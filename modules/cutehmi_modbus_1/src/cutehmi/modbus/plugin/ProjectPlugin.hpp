#ifndef H_MODULES_CUTEHMI__MODBUS__1_SRC_CUTEHMI_MODBUS_PLUGIN_PROJECTPLUGIN_HPP
#define H_MODULES_CUTEHMI__MODBUS__1_SRC_CUTEHMI_MODBUS_PLUGIN_PROJECTPLUGIN_HPP

#include "../../../../cutehmi.metadata.hpp"
#include "../../../../include/cutehmi/modbus/internal/LibmodbusConnection.hpp"

#include <cutehmi/xml/ParseHelper.hpp>
#include <cutehmi/xml/BackendPlugin.hpp>

#include <cutehmi/IProjectPlugin.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace modbus {
namespace plugin {

class ProjectPlugin:
	public QObject,
	public IProjectPlugin,
	public xml::IBackendPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_IPROJECTPLUGIN_IID FILE "../../../../cutehmi.metadata.json")
	Q_INTERFACES(cutehmi::IProjectPlugin)

	friend class PluginTest;

	public:
		// IProjectPlugin
		void init(ProjectNode & node) override;

		// xml::IBackendPlugin
		void readXML(QXmlStreamReader & xmlReader, ProjectNode & node) override;

		// xml::IBackendPlugin
		void writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const noexcept(false) override;

	private:
		void parseModbus(const xml::ParseHelper & parentHelper, ProjectNode & node, const QString & id, const QString & name);

		void parseTCP(const xml::ParseHelper & parentHelper, std::unique_ptr<internal::AbstractConnection> & connection);

		void parseRTU(const xml::ParseHelper & parentHelper, std::unique_ptr<internal::AbstractConnection> & connection);

		void parseDummy(const xml::ParseHelper & parentHelper, std::unique_ptr<internal::AbstractConnection> & connection);

		bool timeoutFromString(const QString & timeoutString, internal::LibmodbusConnection::Timeout & timeout);

		bool secUsecFromString(const QString & timeoutString, unsigned long & sec, unsigned long & usec);
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
