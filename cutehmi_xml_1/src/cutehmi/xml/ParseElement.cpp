#include "../../../include/cutehmi/xml/ParseElement.hpp"

namespace cutehmi {
namespace xml {

ParseElement::AttributesContainer::AttributesContainer(std::initializer_list<ParseAttribute> list)
{
	for (auto && attr: list)
		addAttribute(attr);
}

ParseElement::AttributesContainer & ParseElement::AttributesContainer::operator <<(const ParseAttribute & attribute)
{
	addAttribute(attribute);
	return *this;
}

void ParseElement::AttributesContainer::addAttribute(const ParseAttribute & attribute)
{
	insert(attribute.key(), attribute);
}

ParseElement::AttributesContainer::KeysContainer ParseElement::AttributesContainer::keys() const
{
	return Parent::keys();
}

bool ParseElement::AttributesContainer::containsKey(const QString & attributeKey) const
{
	return Parent::contains(attributeKey);
}

ParseElement::ParseElement(const QString & name, int minOccurrences, int maxOccurrences):
	m(new Members{
	  name,
	  minOccurrences,
	  maxOccurrences,
	  0,
	  AttributesContainer()
	})
{
}

ParseElement::ParseElement(const QString & name, const AttributesContainer & attributes, int minOccurrences, int maxOccurrences):
	m(new Members{
	  name,
	  minOccurrences,
	  maxOccurrences,
	  0,
	  attributes
	})
{

}

ParseElement::ParseElement(const ParseElement & other):
	m(new Members{
	  other.m->name,
	  other.m->minOccurrences,
	  other.m->maxOccurrences,
	  other.m->occurrences,
	  other.m->attributes
	})
{
}

ParseElement & ParseElement::operator =(const ParseElement & other)
{
	// Copy self-assignment branch not required here.
	m->name = other.m->name;
	m->minOccurrences = other.m->minOccurrences;
	m->maxOccurrences = other.m->maxOccurrences;
	m->occurrences = other.m->occurrences;
	m->attributes = other.m->attributes;
	return *this;
}

const QString & ParseElement::name() const
{
	return m->name;
}

int ParseElement::minOccurrences() const
{
	return m->minOccurrences;
}

int ParseElement::maxOccurrences() const
{
	return m->maxOccurrences;
}

int ParseElement::occurrences() const
{
	return m->occurrences;
}

void ParseElement::incOccurences(int value)
{
	m->occurrences += value;
}

ParseElement::AttributesContainer & ParseElement::attributes()
{
	return m->attributes;
}

const ParseElement::AttributesContainer & ParseElement::attributes() const
{
	return m->attributes;
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
