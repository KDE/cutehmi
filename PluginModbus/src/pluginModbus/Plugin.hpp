#ifndef CUTEHMI_PLUGINMODBUS_SRC_PLUGINMODBUS_PLUGIN_HPP
#define CUTEHMI_PLUGINMODBUS_SRC_PLUGINMODBUS_PLUGIN_HPP

#include <base/IPLCPlugin.hpp>
#include <modbus/LibmodbusConnection.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace pluginModbus {

class Plugin:
	public QObject,
	public base::IPLCPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "CuteHMI.PluginModbus" FILE "PluginModbus.json")
	Q_INTERFACES(cutehmi::base::IPLCPlugin)

	friend class PluginTest;

	public:
		base::Error readXML(QXmlStreamReader & xmlReader, base::ProjectModel::Node & node) override;

		base::Error writeXML(QXmlStreamWriter & xmlWriter) const override;

	private:
		base::Error dummyConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection);

		base::Error tcpConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection);

		base::Error rtuConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection);

		base::Error connectionTimeoutsFromXML(QXmlStreamReader & xmlReader, modbus::LibmodbusConnection::Timeout & byteTimeout, modbus::LibmodbusConnection::Timeout & responseTimeout);

		base::Error timeoutFromString(const QString & timeoutString, modbus::LibmodbusConnection::Timeout & timeout);

		base::Error secUsecFromString(const QString & timeoutString, unsigned long & sec, unsigned long & usec);

//		metaData() const;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
