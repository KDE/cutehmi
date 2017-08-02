#include "macros.hpp"
#include "Plugin.hpp"
#include "PluginNodeData.hpp"
#include "ModbusNodeData.hpp"

#include <modbus/internal/TCPConnection.hpp>
#include <modbus/internal/RTUConnection.hpp>
#include <modbus/internal/DummyConnection.hpp>

#include <services/ServiceRegistry.hpp>

#include <base/XMLBackendPlugin.hpp>
#include <base/Exception.hpp>

#include <QtDebug>

namespace cutehmi {
namespace modbus {
namespace plugin {

void Plugin::init(base::ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
	node.addExtension(pluginNodeData->xmlBackendPlugin());
	node.data().append(std::move(pluginNodeData));
}

void Plugin::readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node)
{
	CUTEHMI_MODBUS_PLUGIN_QDEBUG("Plugin 'cutehmi_modbus_1' starts parsing its own portion of document...");

	QStringList supportedVersions;
	supportedVersions << "http://michpolicht.github.io/CuteHMI/ModbusPlugin/xsd/1.0/";

	base::xml::ParseHelper helper(& xmlReader, supportedVersions);
	helper << base::xml::ParseElement("cutehmi_modbus_1", 1, 1);

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "cutehmi_modbus_1") {
			base::xml::ParseHelper nodeHelper(& helper);
			nodeHelper << base::xml::ParseElement("modbus", {base::xml::ParseAttribute("id"),
															 base::xml::ParseAttribute("name")}, 0);
			while (nodeHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "modbus")
					parseModbus(nodeHelper, node, xmlReader.attributes().value("id").toString(), xmlReader.attributes().value("name").toString());
			}
		}
	}
}

void Plugin::writeXML(QXmlStreamWriter & xmlWriter, base::ProjectNode & node) const
{
	Q_UNUSED(xmlWriter);
	Q_UNUSED(node);
	throw base::Exception("cutehmi::modbus::plugin::Plugin::writeXML() not implemented yet.");
}

void Plugin::parseModbus(const base::xml::ParseHelper & parentHelper, base::ProjectNode & node, const QString & id, const QString & name)
{
	base::xml::ParseHelper helper(& parentHelper);
	helper << base::xml::ParseElement("client", 1, 1)
		   << base::xml::ParseElement("service", 1, 1);

	std::unique_ptr<Client> client;
	std::unique_ptr<Service> service;
	std::unique_ptr<internal::AbstractConnection> connection;
	unsigned long serviceSleep = 0;

	QXmlStreamReader & xmlReader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "client") {
			base::xml::ParseHelper clientHelper(& helper);
			clientHelper << base::xml::ParseElement("connection", {base::xml::ParseAttribute("type", "TCP|RTU|dummy")}, 1, 1);

			while (clientHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "connection") {
					if (xmlReader.attributes().value("type") == "TCP")
						parseTCP(clientHelper, connection);
					else if (xmlReader.attributes().value("type") == "RTU")
						parseRTU(clientHelper, connection);
					else if (xmlReader.attributes().value("type") == "dummy")
						parseDummy(clientHelper, connection);
				}
			}
		} else if (xmlReader.name() == "service") {
			base::xml::ParseHelper serviceHelper(& helper);
			serviceHelper << base::xml::ParseElement("sleep", 1, 1);

			while (serviceHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "sleep") {
					bool ok;
					serviceSleep = xmlReader.readElementText().toULong(& ok);
					if (!ok)
						xmlReader.raiseError(QObject::tr("Could not convert 'sleep' element contents to long integer."));
				}
			}
		}
	}

	client.reset(new Client(std::move(connection)));
	service.reset(new Service(name, client.get()));
	service->setSleep(serviceSleep);
	base::ProjectNode * modbusNode = node.addChild(id, base::ProjectNode::Data(name));
	modbusNode->addExtension(client.get());
	modbusNode->addExtension(service.get());

	if (node.root()->child("cutehmi_services_1")) {
		services::ServiceRegistry * serviceRegistry = qobject_cast<services::ServiceRegistry *>(node.root()->child("cutehmi_services_1")->extension(services::ServiceRegistry::staticMetaObject.className()));
		CUTEHMI_BASE_ASSERT(serviceRegistry != nullptr, "pointer must not be nullptr");
		serviceRegistry->add(service.get());
	} else
		CUTEHMI_MODBUS_PLUGIN_QWARNING("Plugin 'cutehmi_services_1' not available.");

	modbusNode->data().append(std::unique_ptr<ModbusNodeData>(new ModbusNodeData(std::move(client), std::move(service))));
}

void Plugin::parseTCP(const base::xml::ParseHelper & parentHelper, std::unique_ptr<internal::AbstractConnection> & connection)
{
	QString name;
	QString service;
	internal::LibmodbusConnection::Timeout byteTimeout;
	internal::LibmodbusConnection::Timeout responseTimeout;
	std::unique_ptr<internal::TCPConnection> tcpConnection;
	int unitId = MODBUS_TCP_SLAVE;

	base::xml::ParseHelper helper(& parentHelper);
	helper << base::xml::ParseElement("node", 1, 1)
		   << base::xml::ParseElement("service", 1, 1)
		   << base::xml::ParseElement("byte_timeout", 1, 1)
		   << base::xml::ParseElement("response_timeout", 1, 1)
		   << base::xml::ParseElement("unit_id", 1, 1);

	QXmlStreamReader & xmlReader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "node")
			name = xmlReader.readElementText();
		else if (xmlReader.name() == "service")
			service = xmlReader.readElementText();
		else if (xmlReader.name() == "byte_timeout") {
			if (!timeoutFromString(xmlReader.readElementText(), byteTimeout))
				xmlReader.raiseError(QObject::tr("Could not parse 'byte_timeout' element."));
		} else if (xmlReader.name() == "response_timeout") {
			if (!timeoutFromString(xmlReader.readElementText(), responseTimeout))
				xmlReader.raiseError(QObject::tr("Could not parse 'response_timeout' element."));
		} else if (xmlReader.name() == "unit_id") {
			bool ok;
			unitId = xmlReader.readElementText().toInt(& ok);
			if (!ok)
				xmlReader.raiseError(QObject::tr("Could not convert 'unit_id' element contents to integer."));
		}
	}
	tcpConnection.reset(new internal::TCPConnection(name, service, unitId));
	tcpConnection->setByteTimeout(byteTimeout);
	tcpConnection->setResponseTimeout(responseTimeout);
	connection.reset(tcpConnection.release());
}

void Plugin::parseRTU(const base::xml::ParseHelper & parentHelper, std::unique_ptr<internal::AbstractConnection> & connection)
{
	QString port;
	int baudRate = 19200;
	internal::RTUConnection::Parity parity = internal::RTUConnection::Parity::NONE;
	internal::RTUConnection::DataBits dataBits = internal::RTUConnection::DataBits::BITS_8;
	internal::RTUConnection::StopBits stopBits = internal::RTUConnection::StopBits::BITS_1;
	internal::RTUConnection::Mode mode = internal::RTUConnection::Mode::RS232;
	int slaveId = 1;
	internal::LibmodbusConnection::Timeout byteTimeout;
	internal::LibmodbusConnection::Timeout responseTimeout;
	std::unique_ptr<internal::RTUConnection> rtuConnection;

	base::xml::ParseHelper helper(& parentHelper);
	helper << base::xml::ParseElement("port", 1, 1)
		   << base::xml::ParseElement("baud_rate", 1, 1)
		   << base::xml::ParseElement("parity", 1, 1)
		   << base::xml::ParseElement("data_bits", 1, 1)
		   << base::xml::ParseElement("stop_bits", 1, 1)
		   << base::xml::ParseElement("mode", 1, 1)
		   << base::xml::ParseElement("slave_id", 1, 1);

	QXmlStreamReader & xmlReader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "port")
			port = xmlReader.readElementText();
		else if (xmlReader.name() == "baud_rate") {
			bool ok;
			baudRate = xmlReader.text().toInt(& ok);
			if (!ok)
				xmlReader.raiseError(QObject::tr("Could not convert 'baud_rate' element contents to integer."));
		} else if (xmlReader.name() == "parity") {
			QString parityText = xmlReader.readElementText();
			if (parityText == "NONE")
				parity = internal::RTUConnection::Parity::NONE;
			else if (parityText == "ODD")
				parity = internal::RTUConnection::Parity::ODD;
			else if (parityText == "EVEN")
				parity = internal::RTUConnection::Parity::EVEN;
			else
				xmlReader.raiseError(QObject::tr("Contents of 'parity' element must match pattern 'NONE|ODD|EVEN'."));
		} else if (xmlReader.name() == "data_bits") {
			bool ok;
			dataBits = static_cast<internal::RTUConnection::DataBits>(xmlReader.readElementText().toInt(& ok));
			if (!ok)
				xmlReader.raiseError(QObject::tr("Could not convert 'data_bits' element contents to integer."));
		} else if (xmlReader.name() == "stop_bits") {
			bool ok;
			stopBits = static_cast<internal::RTUConnection::StopBits>(xmlReader.readElementText().toInt(& ok));
			if (!ok)
				xmlReader.raiseError(QObject::tr("Could not convert 'stop_bits' element contents to integer."));
		} else if (xmlReader.name() == "mode") {
			QString modeText = xmlReader.readElementText();
			if (modeText == "RS232")
				mode = internal::RTUConnection::Mode::RS232;
//<workaround id="ModbusLib-1" target="libmodbus" cause="bug">
//			else if (modeText == "RS485")
//				mode = internal::RTUConnection::Mode::RS485;
//</workaround>
			else
				xmlReader.raiseError(QObject::tr("Contents of 'mode' element must match pattern 'RS232'."));
		} else if (xmlReader.name() == "slave_id") {
			bool ok;
			slaveId = xmlReader.readElementText().toInt(& ok);
			if (!ok)
				xmlReader.raiseError(QObject::tr("Could not convert 'slave_id' element contents to integer."));
		} else if (xmlReader.name() == "byte_timeout") {
			if (!timeoutFromString(xmlReader.readElementText(), byteTimeout))
				xmlReader.raiseError(QObject::tr("Could not parse 'byte_timeout' element."));
		} else if (xmlReader.name() == "response_timeout") {
			if (!timeoutFromString(xmlReader.readElementText(), responseTimeout))
				xmlReader.raiseError(QObject::tr("Could not parse 'response_timeout' element."));
		}
	}

	rtuConnection.reset(new internal::RTUConnection(port, baudRate, parity, dataBits, stopBits, mode, slaveId));
	rtuConnection->setByteTimeout(byteTimeout);
	rtuConnection->setResponseTimeout(responseTimeout);
	connection.reset(rtuConnection.release());
}

void Plugin::parseDummy(const base::xml::ParseHelper & parentHelper, std::unique_ptr<internal::AbstractConnection> & connection)
{
	unsigned long latency = 0;
	unsigned long connectLatency = 0;
	unsigned long disconnectLatency = 0;
	std::unique_ptr<internal::DummyConnection> dummyConnection;

	base::xml::ParseHelper helper(& parentHelper);
	helper << base::xml::ParseElement("latency", 1, 1)
		   << base::xml::ParseElement("connect_latency", 1, 1)
		   << base::xml::ParseElement("disconnect_latency", 1, 1);

	QXmlStreamReader & xmlReader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "latency") {
			bool ok;
			latency = xmlReader.readElementText().toULong(& ok);
			if (!ok)
				xmlReader.raiseError(QObject::tr("Could not convert 'latency' element data to long integer."));
		} else if (xmlReader.name() == "connect_latency") {
			bool ok;
			connectLatency = xmlReader.readElementText().toULong(& ok);
			if (!ok)
				xmlReader.raiseError(QObject::tr("Could not convert 'connect_latency' element data to long integer."));
		} else if (xmlReader.name() == "disconnect_latency") {
			bool ok;
			disconnectLatency = xmlReader.readElementText().toULong(& ok);
			if (!ok)
				xmlReader.raiseError(QObject::tr("Could not convert 'disconnect_latency' element data to long integer."));
		}
	}
	dummyConnection.reset(new internal::DummyConnection);
	dummyConnection->setLatency(latency);
	dummyConnection->setConnectLatency(connectLatency);
	dummyConnection->setDisconnectLatency(disconnectLatency);
	connection.reset(dummyConnection.release());
}

bool Plugin::timeoutFromString(const QString & timeoutString, internal::LibmodbusConnection::Timeout & timeout)
{
	unsigned long sec, usec;

	if (secUsecFromString(timeoutString, sec, usec)) {
		// unsigned long is guaranteed to be at least 32 bit.
		timeout.sec = sec;
		timeout.usec = usec;
		return true;
	}
	return false;
}

bool Plugin::secUsecFromString(const QString & timeoutString, unsigned long & sec, unsigned long & usec)
{
	bool okSec, okUsec;

	QStringList secUsec = timeoutString.split(".");
	if (secUsec.length() != 2)
		return false;
	if (secUsec.value(1).count() > 6)
		CUTEHMI_MODBUS_PLUGIN_QDEBUG("Values smaller than a microsecond will be ignored.");
	sec = secUsec.value(0).toULong(& okSec);
	usec = secUsec.value(1).leftJustified(6, '0', true).toULong(& okUsec); // unsigned long is guaranteed to be at least 32 bit.
	if (!okSec || !okUsec)
		return false;
	return true;
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
