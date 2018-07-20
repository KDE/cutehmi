#ifndef H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_PROJECTBACKEND_HPP
#define H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_PROJECTBACKEND_HPP

#include "internal/common.hpp"
#include "internal/functions.hpp"
#include "ParseHelper.hpp"

#include <cutehmi/ExceptionMixin.hpp>
#include <cutehmi/ProjectNode.hpp>
#include <cutehmi/ProjectPluginLoader.hpp>
#include <cutehmi/IProjectBackend.hpp>

#include <QXmlStreamReader>
#include <QQmlContext>

class QIODevice;

namespace cutehmi {
namespace xml {

class CUTEHMI_XML_API ProjectBackend:
	public IProjectBackend
{
	public:
		class Exception:
			public ExceptionMixin<Exception>
		{
			typedef ExceptionMixin<Exception> Parent;

			public:
				using Parent::Parent;
		};

		class ParseErrorException:
			public Exception
		{
			public:
				ParseErrorException(const QXmlStreamReader & reader):
					Exception(tr("Parse error.") + padded(reader.errorString()) + tr("Stopped at %1.").arg(xml::internal::readerPositionString(reader)))
				{
				}

			private:
				QString padded(const QString & str)
				{
					if (str.isEmpty())
						return str;
					return QString(" ") + str + " ";
				}
		};

		class DeviceOpenReadException:
			public Exception
		{
			public:
				DeviceOpenReadException():
					Exception(tr("Could not open the device for reading."))
				{
				}
		};

		/**
		 * Constructor.
		 * @param device device.
		 * @param qmlContext QML context.
		 */
		ProjectBackend(QIODevice * device, QQmlContext * qmlContext);

		void load(const ProjectPluginLoader & pluginLoader, ProjectNode & rootNode) noexcept(false) override;

//		void save(QIODevice * device);

	private:
		struct Loader1
		{
			Loader1(ProjectNode * root, const ProjectPluginLoader * pluginLoader, QQmlContext * qmlContext);

			void parse(const xml::ParseHelper & parentHelper);

			void parsePlugin(const xml::ParseHelper & parentHelper, ProjectNode & node);

			void parseNodeRef(const xml::ParseHelper & parentHelper, ProjectNode & currentNode);

			private:
				ProjectNode * m_root;
				const ProjectPluginLoader * m_pluginLoader;
				QQmlContext * m_qmlContext;
		};

//		struct Saver1 {
//		};

		struct Members
		{
			QXmlStreamReader xmlReader;
			QQmlContext * qmlContext;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
