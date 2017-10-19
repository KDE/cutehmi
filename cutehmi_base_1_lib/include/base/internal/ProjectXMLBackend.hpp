#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_INTERNAL_PROJECTXMLBACKEND_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_INTERNAL_PROJECTXMLBACKEND_HPP

#include "common.hpp"
#include "../ExceptionMixin.hpp"
#include "../ProjectModel.hpp"
#include "../xml/internal/functions.hpp"
#include "../xml/ParseHelper.hpp"

#include <QXmlStreamReader>
#include <QQmlContext>

class QIODevice;

namespace cutehmi {
namespace base {

class PluginLoader;

namespace internal {

class ProjectXMLBackend
{
	public:
		class Exception:
			public base::ExceptionMixin<Exception>
		{
			typedef base::ExceptionMixin<Exception> Parent;

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

		class MissingInterfaceException:
			public Exception
		{
			public:
				MissingInterfaceException(const QString & binary, const QString & pluginVersion, const QString & interface):
					Exception(tr("Plugin '%1' version '%2' does not implement required interface '%3'.").arg(binary).arg(pluginVersion).arg(interface))
				{
				}
		};

		class MissingExtensionException:
			public Exception
		{
			public:
				MissingExtensionException(const QString & binary, const QString & pluginVersion, const QString & interface):
					Exception(tr("Plugin '%1' version '%2' does not provide required extension '%3'.").arg(binary).arg(pluginVersion).arg(interface))
				{
				}
		};

		/**
		 * Constructor.
		 * @param model project model.
		 * @param pluginLoader properly configured plugin loader.
		 * @param qmlContext QML context.
		 */
		ProjectXMLBackend(ProjectModel * model, PluginLoader * pluginLoader, QQmlContext * qmlContext);

		/**
		 * Load XML.
		 * @param device device to read from.
		 *
		 * @throws ExtErrorException in case of error.
		 */
		void load(QIODevice & device);

//		void save(QIODevice * device);

	private:
		struct Loader1
		{
			Loader1(ProjectNode * root, PluginLoader * pluginLoader, QQmlContext * qmlContext);

			void parse(const xml::ParseHelper & parentHelper);

			void parsePlugin(const xml::ParseHelper & parentHelper, ProjectNode & node);

			void parseNodeRef(const xml::ParseHelper & parentHelper, ProjectNode & currentNode);

			private:
				ProjectNode * m_root;
				PluginLoader * m_pluginLoader;
				QQmlContext * m_qmlContext;
		};

//		struct Saver1 {
//		};

		struct Members
		{
			QXmlStreamReader xmlReader;
			ProjectModel * model;
			PluginLoader * pluginLoader;
			QQmlContext * qmlContext;
		};

		utils::MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
