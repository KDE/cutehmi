#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_XML_PARSEHELPER_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_XML_PARSEHELPER_HPP

#include "../internal/common.hpp"
#include "ParseElement.hpp"

#include <utils/NonCopyable.hpp>

#include <QVector>
#include <QXmlStreamReader>

#include <memory>

namespace cutehmi {
namespace base {
namespace xml {

class CUTEHMI_BASE_API ParseHelper:
	utils::NonCopyable
{
	friend class ParseHelperTest;

	public:
		ParseHelper(QXmlStreamReader * reader, const QString & namespaceURI = QString());

		ParseHelper & operator <<(const ParseElement & element);

		void addElement(const ParseElement & element);

		QXmlStreamReader * xmlReader() const;

		QString namespaceURI() const;

		bool readNextRecognizedElement();

	protected:
		/**
		 * Skip to next sibling element. This function sets reader on the next start tag of next sibling
		 * element. It skips all children elements (if any). If there are no more sibling elements
		 * function returns @p false.
		 * @return @p true, when next sibling element has been reached, @p false otherwise.
		 */
		bool skipToNextSiblingElement();

	private:
		typedef QMap<QString, ParseElement> ElementsContainer;

		QXmlStreamReader * xmlReader();

		ParseElement * findElement(const QString & name);

		bool checkAttributes(QXmlStreamReader & reader, const ParseElement & element);

		struct Members
		{
			QXmlStreamReader * xmlReader;
			QString namespaceURI;
			ElementsContainer elements;
			int level;
		};

		utils::MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
