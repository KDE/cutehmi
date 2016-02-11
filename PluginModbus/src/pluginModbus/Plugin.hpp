#ifndef CUTEHMI_PLUGINMODBUS_SRC_PLUGINMODBUS_PLUGIN_HPP
#define CUTEHMI_PLUGINMODBUS_SRC_PLUGINMODBUS_PLUGIN_HPP

#include <plugin/IPLCClient.hpp>
#include <plugin/IXMLBackend.hpp>
#include <modbus/AbstractConnection.hpp>

#include <QObject>

#include <memory>

namespace pluginModbus {

class Plugin:
	public QObject,
	public plugin::IPLCClient,
	public plugin::IXMLBackend
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "CuteHMI.PluginModbus" FILE "PluginModbus.json")
	Q_INTERFACES(plugin::IPLCClient plugin::IXMLBackend)

	public:
		base::Error readXML(QXmlStreamReader & xmlReader, base::ProjectModel::Node & node) override;

		base::Error writeXML(QXmlStreamWriter & xmlWriter) const override;

	private:
		class VisitorDelegate:
			public base::ProjectModel::Node::VisitorDelegate
		{
			public:
				VisitorDelegate(const base::ProjectModel::Node * node);

				void visit(QQmlContext & context) override;

			private:
				const base::ProjectModel::Node * m_node;
		};

		base::Error tcpConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection);

		base::Error rtuConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection);

		base::Error connectionTimeoutsFromXML(QXmlStreamReader & xmlReader, modbus::AbstractConnection::Timeout & byteTimeout, modbus::AbstractConnection::Timeout & responseTimeout);

		base::Error timeoutFromString(const QString & timeoutString, modbus::AbstractConnection::Timeout & timeout);

//		metaData() const;
};

}

#endif
