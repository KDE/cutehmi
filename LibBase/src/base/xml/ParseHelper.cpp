#include "../../../include/base/xml/ParseHelper.hpp"
#include "../../../include/base/xml/internal/functions.hpp"

namespace cutehmi {
namespace base {
namespace xml {

ParseHelper::ParseHelper(QXmlStreamReader * reader, const QString & namespaceURI):
	m(new Members{reader, namespaceURI, ElementsContainer(), 0})
{
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

QXmlStreamReader * ParseHelper::xmlReader() const
{
	return m->xmlReader;
}

QString ParseHelper::namespaceURI() const
{
	return m->namespaceURI;
}

bool ParseHelper::readNextRecognizedElement()
{
	while (skipToNextSiblingElement()) {
		if (!m->namespaceURI.isEmpty() && (m->namespaceURI != xmlReader()->namespaceUri())) {
			CUTEHMI_BASE_QWARNING("Element '"<< xmlReader()->name() << "' does not belong to '" << m->namespaceURI << "' namespace at: " << internal::readerPositionString(*xmlReader()) << ".");
			xmlReader()->skipCurrentElement();
			continue;
		}
		ParseElement * element = findElement(xmlReader()->name().toString());
		if (element) {
			element->incOccurences();
			if ((element->maxOccurrences() >= 0) && (element->occurrences() > element->maxOccurrences())) {
				xmlReader()->raiseError(QObject::tr("Too many occurences (%1) of '<%2>' element.").arg(element->occurrences()).arg(element->name()));
				return false;
			}
			return checkAttributes(*xmlReader(), *element);
		} else {
			CUTEHMI_BASE_QWARNING("Unrecognized element '"<< xmlReader()->name() << "' at: " << internal::readerPositionString(*xmlReader()) << ".");
			xmlReader()->skipCurrentElement();
		}
	}

	// If error was not raised by another helper operatring on child elements, then check if all required elements were present and raise error if necessary.
	if (!xmlReader()->hasError())
		for (const ParseElement & element: m->elements) {
			if (element.occurrences() < element.minOccurrences()) {
				xmlReader()->raiseError(QObject::tr("Parent element requires %n occurrence(s) of '<%1>' element (encountered %2).", "", element.minOccurrences())
										.arg(element.name())
										.arg(element.occurrences()));
				return false;
			}
		}
	return false;
}

bool ParseHelper::skipToNextSiblingElement()
{
	QXmlStreamReader::TokenType token = xmlReader()->tokenType();
	while (token != QXmlStreamReader::Invalid && token != QXmlStreamReader::EndDocument) {
		if (xmlReader()->isEndElement()) {
			m->level--;
			if (m->level == -1)
				return false;
		}
		token = xmlReader()->readNext();
		if (xmlReader()->isStartElement()) {
			m->level++;
			if (m->level == 1)
				return true;
			else if (m->level == 2)
				CUTEHMI_BASE_QWARNING("Skipping child element: " << internal::readerPositionString(*xmlReader()) << ".");
		}
	}
	return false;
}

QXmlStreamReader * ParseHelper::xmlReader()
{
	return m->xmlReader;
}

ParseElement * ParseHelper::findElement(const QString & name)
{
	ElementsContainer::iterator result = m->elements.find(name);
	if (result == m->elements.end())
		return nullptr;
	return & (*result);
}

bool ParseHelper::checkAttributes(QXmlStreamReader & reader, const ParseElement & element)
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
			CUTEHMI_BASE_QWARNING("Element '" << element.name() << "' contains unrecognized attribute '" << attr.name().toString() << "' at: " << internal::readerPositionString(*xmlReader()) << ".");

	return true;
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
