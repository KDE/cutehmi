#include "../../../include/cutehmi/xml/ParseHelper.hpp"
#include "../../../include/cutehmi/xml/internal/functions.hpp"

namespace cutehmi {
namespace base {
namespace xml {

ParseHelper::ParseHelper(QXmlStreamReader * reader, const QString & namespaceURI):
	m(new Members{reader, {namespaceURI}, ElementsContainer(), 0, nullptr, nullptr, QString()})
{
}

ParseHelper::ParseHelper(QXmlStreamReader * reader, const QStringList & namespaceURIList):
	m(new Members{reader, namespaceURIList, ElementsContainer(), 0, nullptr, nullptr, QString()})
{
}

ParseHelper::ParseHelper(const ParseHelper * parentHelper):
	m(new Members{parentHelper->m->xmlReader, parentHelper->namespaceURIList(), ElementsContainer(), 0, nullptr, parentHelper, parentHelper->lastRecognizedNamespaceURI()})
{
}

ParseHelper::operator const QXmlStreamReader &() const
{
	return *m->xmlReader;
}

ParseHelper::operator QXmlStreamReader &()
{
	return *m->xmlReader;
}

ParseHelper & ParseHelper::operator <<(const ParseElement & element)
{
	addElement(element);
	return *this;
}

void ParseHelper::addElement(const ParseElement & element)
{
	m->elements.insert(element.name(), element);
}

const QXmlStreamReader & ParseHelper::xmlReader() const
{
	return *m->xmlReader;
}

QStringList ParseHelper::namespaceURIList() const
{
	return m->namespaceURIList;
}

const ParseHelper * ParseHelper::parentHelper() const
{
	return m->parentHelper;
}

bool ParseHelper::readNextRecognizedElement()
{
	m->lastRecognizedElement = nullptr;

	while (skipToNextSiblingElement()) {
		if (!m->namespaceURIList.isEmpty() && (!checkNamespace(m->xmlReader->namespaceUri().toString()))) {
			m->xmlReader->raiseError(QObject::tr("Element '<%1 [...] xmlns=\"%2\">' does not belong to any of the supported namespaces. Supported namespaces: '%3'.")
									.arg(m->xmlReader->name().toString())
									.arg(m->xmlReader->namespaceUri().toString())
									.arg(m->namespaceURIList.join("', '")));
			return false;
		}
		ParseElement * element = findElement(m->xmlReader->name().toString());
		if (element) {
			element->incOccurences();
			if ((element->maxOccurrences() >= 0) && (element->occurrences() > element->maxOccurrences())) {
				m->xmlReader->raiseError(QObject::tr("Too many occurences (%1) of '<%2>' element within %3.").arg(element->occurrences()).arg(element->name()).arg(withinString()));
				return false;
			}
			if (checkAttributes(*m->xmlReader, *element)) {
				m->lastRecognizedElement = element;
				return true;
			} else
				return false;
		} else {
			m->xmlReader->raiseError(QObject::tr("Unrecognized element '<%1>' within %2.").arg(m->xmlReader->name().toString()).arg(withinString()));
			return false;
		}
	}

	// If error was not raised by another helper operatring on child elements, then check if all required elements were present and raise error if necessary.
	if (!m->xmlReader->hasError())
		for (const ParseElement & element: m->elements) {
			if (element.occurrences() < element.minOccurrences()) {
				m->xmlReader->raiseError(QObject::tr("There must be at least %n occurrence(s) of '<%1>' element (encountered %2) within %3.", "", element.minOccurrences())
										.arg(element.name())
										.arg(element.occurrences())
										.arg(withinString()));
				return false;
			}
		}
	return false;
}

QString ParseHelper::readElementText()
{
	return m->xmlReader->readElementText();
}

const ParseElement * ParseHelper::lastRecognizedElement() const
{
	return m->lastRecognizedElement;
}

QString ParseHelper::lastRecognizedNamespaceURI() const
{
	return m->lastRecognizedNamespaceURI;
}

void ParseHelper::raiseError(const QString & message)
{
	m->xmlReader->raiseError(message);
}

bool ParseHelper::skipToNextSiblingElement()
{
	QXmlStreamReader::TokenType token = m->xmlReader->tokenType();
	while (token != QXmlStreamReader::Invalid && token != QXmlStreamReader::EndDocument) {
		if (m->xmlReader->isEndElement()) {
			m->level--;
			if (m->level == -1)
				return false;
		}
		token = m->xmlReader->readNext();
		if (m->xmlReader->isStartElement()) {
			m->level++;
			if (m->level == 1)
				return true;
			else if (m->level == 2)
				CUTEHMI_LOG_WARNING("Skipping child element: " << internal::readerPositionString(*m->xmlReader) << ".");
		}
	}
	return false;
}

ParseElement * ParseHelper::findElement(const QString & name)
{
	ElementsContainer::iterator result = m->elements.find(name);
	if (result == m->elements.end())
		return nullptr;
	return & (*result);
}

bool ParseHelper::checkAttributes(QXmlStreamReader & reader, const ParseElement & element) const
{
	// Look for required attributes.
	for (const ParseAttribute & reqAttr : element.attributes()) {
		if (!reqAttr.required())
			continue;
		if (reader.attributes().hasAttribute(reqAttr.key())) {
			QStringRef readerAttributeValue = reader.attributes().value(reqAttr.key());
			if (!reqAttr.valuesRegExp().isEmpty()) {
				// Check values.
				if (!reqAttr.valuesRegExp().exactMatch(readerAttributeValue.toString())) {
					reader.raiseError(QObject::tr("Element '<%1 [...] %2=\"%3\">' has invalid attribute value. Value of '%2' attribute must match '%4' pattern.")
									  .arg(element.name())
									  .arg(reqAttr.key())
									  .arg(readerAttributeValue.toString())
									  .arg(reqAttr.valuesRegExp().pattern()));
					return false;
				}
			}
		} else {
			reader.raiseError(QObject::tr("Element '<%1>' requires attribute '%2'.").arg(element.name()).arg(reqAttr.key()));
			return false;
		}
	}

	// Warn about unrecognized attributes.
	for (const QXmlStreamAttribute & attr : reader.attributes())
		if (!element.attributes().containsKey(attr.name().toString()))
			CUTEHMI_LOG_WARNING("Element '" << element.name() << "' contains unrecognized attribute '" << attr.name().toString() << "' at: " << internal::readerPositionString(*m->xmlReader) << ".");

	return true;
}

QString ParseHelper::withinString() const
{
	if (parentHelper() != nullptr)
		return QString("'<") + parentHelper()->lastRecognizedElement()->name()
				+ (parentHelper()->lastRecognizedNamespaceURI().isEmpty() ? "\">'" : " [...] xmlns=\"" + parentHelper()->lastRecognizedNamespaceURI() + "\">'");
	else
		return QObject::tr("parent element");
}

bool ParseHelper::checkNamespace(const QString & namespaceURI) const
{
	if (lastRecognizedNamespaceURI() == namespaceURI)
		return true;
	if (namespaceURIList().contains(namespaceURI)) {
		m->lastRecognizedNamespaceURI = namespaceURI;
		return true;
	}
	return false;
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
