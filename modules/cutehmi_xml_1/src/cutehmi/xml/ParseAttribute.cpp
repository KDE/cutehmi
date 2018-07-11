#include "../../../include/cutehmi/xml/ParseAttribute.hpp"

namespace cutehmi {
namespace xml {

ParseAttribute::ParseAttribute(const QString & key, bool required):
	m(new Members{key, QRegExp(), required})
{
}

ParseAttribute::ParseAttribute(const QString & key, const char * valuesPattern, bool required):
	m(new Members{key, QRegExp(valuesPattern), required})
{
	CUTEHMI_ASSERT(m->valuesRegExp.isValid(), "invalid regular expression pattern.");
}

ParseAttribute::ParseAttribute(const QString & key, const QString & valuesPattern, bool required):
	m(new Members{key, QRegExp(valuesPattern), required})
{
	CUTEHMI_ASSERT(m->valuesRegExp.isValid(), "invalid regular expression pattern.");
}

ParseAttribute::ParseAttribute(const QString & key, const QRegExp & valuesRegExp, bool required):
	m(new Members{key, valuesRegExp, required})
{
	CUTEHMI_ASSERT(m->valuesRegExp.isValid(), "invalid regular expression pattern.");
}

ParseAttribute::ParseAttribute(const ParseAttribute & other):
	m(new Members{other.m->key, other.m->valuesRegExp, other.m->required})
{
}

ParseAttribute & ParseAttribute::operator =(const ParseAttribute & other)
{
	// Self-assignment branch not required.
	m->key = other.m->key;
	m->valuesRegExp = other.m->valuesRegExp;
	m->required = other.m->required;
	return *this;
}

const QString & ParseAttribute::key() const
{
	return m->key;
}

const QRegExp & ParseAttribute::valuesRegExp() const
{
	return m->valuesRegExp;
}

bool ParseAttribute::required() const
{
	return m->required;
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
