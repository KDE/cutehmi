#ifndef CUTEHMI_PLUGINMODBUS_SRC_MODBUS_PLUGIN_PLUGIN_HPP
#define CUTEHMI_PLUGINMODBUS_SRC_MODBUS_PLUGIN_PLUGIN_HPP

#include <base/IXMLBackendPlugin.hpp>
#include <base/IPlugin.hpp>

#include <modbus/internal/LibmodbusConnection.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace modbus {
namespace plugin {

class Plugin:
	public QObject,
	public base::IPlugin,
	public base::IXMLBackendPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_BASE_IPLUGIN_IID FILE "PluginModbus.json")
	Q_INTERFACES(cutehmi::base::IPlugin)

	friend class PluginTest;

	public:
		static constexpr const char * NAMESPACE_URI = "http://modbus.cutehmi";

		// base::IPlugin
		void init(base::ProjectNode & node) override;

		// base::IXMLBackendPlugin
		void readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node) override;

		// base::IXMLBackendPlugin
		void writeXML(QXmlStreamWriter & xmlWriter, base::ProjectNode & node) const override;

//		base::Error readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node) override;

//		base::Error writeXML(QXmlStreamWriter & xmlWriter, base::ProjectNode & node) const override;

	private:
		void parseModbus(QXmlStreamReader & xmlReader, base::ProjectNode & node, const QString & id, const QString & name);

		void parseTCP(QXmlStreamReader & xmlReader, std::unique_ptr<internal::AbstractConnection> & connection);

		void parseRTU(QXmlStreamReader & xmlReader, std::unique_ptr<internal::AbstractConnection> & connection);

		void parseDummy(QXmlStreamReader & xmlReader, std::unique_ptr<internal::AbstractConnection> & connection);

		bool timeoutFromString(const QString & timeoutString, internal::LibmodbusConnection::Timeout & timeout);

		bool secUsecFromString(const QString & timeoutString, unsigned long & sec, unsigned long & usec);

//		base::Error dummyConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection);

//		base::Error tcpConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection);

//		base::Error rtuConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection);

//		base::Error connectionTimeoutsFromXML(QXmlStreamReader & xmlReader, modbus::LibmodbusConnection::Timeout & byteTimeout, modbus::LibmodbusConnection::Timeout & responseTimeout);

//		base::Error timeoutFromString(const QString & timeoutString, modbus::LibmodbusConnection::Timeout & timeout);

//		base::Error secUsecFromString(const QString & timeoutString, unsigned long & sec, unsigned long & usec);

//		metaData() const;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
