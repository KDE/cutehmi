#ifndef H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_PARSEHELPER_HPP
#define H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_PARSEHELPER_HPP

#include "internal/common.hpp"
#include "ParseElement.hpp"

#include <QVector>
#include <QXmlStreamReader>

#include <memory>

namespace cutehmi {
namespace xml {

class CUTEHMI_XML_API ParseHelper
{
	friend class ParseHelperTest;

	public:
		ParseHelper(QXmlStreamReader * reader, const QString & namespaceURI = QString());

		ParseHelper(QXmlStreamReader * reader, const QStringList & namespaceURIList = QStringList());

		ParseHelper(const ParseHelper * parentHelper);

		ParseHelper(const ParseHelper & other) = delete;

		ParseHelper & operator =(const ParseHelper & other) = delete;

		explicit operator const QXmlStreamReader & () const;

		explicit operator QXmlStreamReader & ();

		ParseHelper & operator <<(const ParseElement & element);

		void addElement(const ParseElement & element);

		const QXmlStreamReader & xmlReader() const;

		QStringList namespaceURIList() const;

		const ParseHelper * parentHelper() const;

		bool readNextRecognizedElement();

		QString readElementText();

		const ParseElement * lastRecognizedElement() const;

		QString lastRecognizedNamespaceURI() const;

		void raiseError(const QString & message = QString());

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

		ParseElement * findElement(const QString & name);

		bool checkAttributes(QXmlStreamReader & reader, const ParseElement & element) const;

		QString withinString() const;

		bool checkNamespace(const QString & namespaceURI) const;

		struct Members
		{
			QXmlStreamReader * xmlReader;
			QStringList namespaceURIList;
			ElementsContainer elements;
			int level;
			const ParseElement * lastRecognizedElement;
			const ParseHelper * parentHelper;
			mutable QString lastRecognizedNamespaceURI;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
