#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_XML_PARSEATTRIBUTE_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_XML_PARSEATTRIBUTE_HPP

#include "../internal/common.hpp"

#include <memory>

#include <QRegExp>

namespace cutehmi {
namespace base {
namespace xml {

/**
 * Parse attribute.
 */
class CUTEHMI_BASE_API ParseAttribute
{
	friend class ParseAttributeTest;

	public:
		explicit ParseAttribute(const QString & key, bool required = true);

		ParseAttribute(const QString & key, const char * valuesPattern, bool required = true);

		ParseAttribute(const QString & key, const QString & valuesPattern, bool required = true);

		ParseAttribute(const QString & key, const QRegExp & valuesRegExp, bool required = true);

		ParseAttribute(const ParseAttribute & other);

		ParseAttribute(ParseAttribute && other) = default;

		ParseAttribute & operator =(const ParseAttribute & other);

		ParseAttribute & operator =(ParseAttribute && other) = default;

		const QString & key() const;

		const QRegExp & valuesRegExp() const;

		bool required() const;

	private:
		struct Members
		{
			QString key;
			QRegExp valuesRegExp;
			bool required;
		};

		std::unique_ptr<Members> m;
};

}
}
}

/**
 * Comparison operator.
 * @param attr1 first parse attribute.
 * @param attr2 second parse attribute.
 * @return @p true if both are equal, @p false otherwise.
 *
 * @warning two parse attributes are equal if their keys are equal.
 */
inline bool operator ==(const cutehmi::base::xml::ParseAttribute & attr1, const cutehmi::base::xml::ParseAttribute & attr2)
{
	return attr1.key() == attr2.key();
}

inline uint qHash(const cutehmi::base::xml::ParseAttribute & attr, uint seed)
{
	return qHash(attr.key(), seed);
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
