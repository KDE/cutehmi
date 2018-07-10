#ifndef H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_PARSEELEMENT_HPP
#define H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_PARSEELEMENT_HPP

#include "internal/common.hpp"
#include "ParseAttribute.hpp"

#include <QMap>

#include <memory>

namespace cutehmi {
namespace xml {

class CUTEHMI_XML_API ParseElement
{
	friend class ParseElementTest;

	public:
		class CUTEHMI_XML_API AttributesContainer:
			protected QMap<QString, ParseAttribute>
		{
			friend class ParseElementTest;

			typedef QMap<QString, ParseAttribute> Parent;

			public:
				typedef QList<QString> KeysContainer;

				AttributesContainer() = default;

				AttributesContainer(const AttributesContainer & other) = default;

				AttributesContainer(AttributesContainer && other) = default;

				AttributesContainer(std::initializer_list<ParseAttribute> list);

				AttributesContainer & operator =(const AttributesContainer & other) = default;

				AttributesContainer & operator =(AttributesContainer && other) = default;

				AttributesContainer & operator <<(const ParseAttribute & attribute);

				using Parent::begin;
				using Parent::cbegin;

				using Parent::end;
				using Parent::cend;

				using Parent::clear;

				using Parent::count;

				using Parent::isEmpty;

				void addAttribute(const ParseAttribute & attribute);

				KeysContainer keys() const;

				bool containsKey(const QString & attributeKey) const;
		};

		explicit ParseElement(const QString & name = QString(), int minOccurrences = 1, int maxOccurrences = -1);

		ParseElement(const QString & name, const AttributesContainer & attributes, int minOccurrences = 1, int maxOccurrences = -1);

		ParseElement(const ParseElement & other);

		ParseElement(ParseElement && other) = default;

		ParseElement & operator =(const ParseElement & other);

		ParseElement & operator =(ParseElement && other) = default;

		const QString & name() const;

		int minOccurrences() const;

		int maxOccurrences() const;

		int occurrences() const;

		void incOccurences(int value = 1);

		AttributesContainer & attributes();

		const AttributesContainer & attributes() const;

	private:
		struct Members
		{
			QString name;
			int minOccurrences;
			int maxOccurrences;
			int occurrences;
			AttributesContainer attributes;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
