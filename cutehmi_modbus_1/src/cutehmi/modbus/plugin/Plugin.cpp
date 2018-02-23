#include "Plugin.hpp"
#include "PluginNodeData.hpp"
#include "ModbusNodeData.hpp"
#include "../../../../include/cutehmi/modbus/logging.hpp"
#include "../../../../include/cutehmi/modbus/internal/TCPConnection.hpp"
#include "../../../../include/cutehmi/modbus/internal/RTUConnection.hpp"
#include "../../../../include/cutehmi/modbus/internal/DummyConnection.hpp"

#include <cutehmi/services/ServiceRegistry.hpp>

#include <cutehmi/XMLBackendPlugin.hpp>
#include <cutehmi/Exception.hpp>

#include <QtDebug>

namespace cutehmi {
namespace modbus {
namespace plugin {

void Plugin::init(ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
	node.addExtension(pluginNodeData->xmlBackendPlugin());
	node.data().append(std::move(pluginNodeData));
}

void Plugin::readXML(QXmlStreamReader & xmlReader, ProjectNode & node)
{
	CUTEHMI_LOG_DEBUG("Plugin 'cutehmi_modbus_1' starts parsing its own portion of document...");

	QStringList supportedVersions;
	supportedVersions << "http://michpolicht.github.io/CuteHMI/cutehmi_modbus_1/xsd/1.0/";

	xml::ParseHelper helper(& xmlReader, supportedVersions);
	helper << xml::ParseElement("cutehmi_modbus_1", 1, 1);

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "cutehmi_modbus_1") {
			xml::ParseHelper nodeHelper(& helper);
			nodeHelper << xml::ParseElement("modbus", {xml::ParseAttribute("id"),
															 xml::ParseAttribute("name")}, 0);
			while (nodeHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "modbus")
					parseModbus(nodeHelper, node, xmlReader.attributes().value("id").toString(), xmlReader.attributes().value("name").toString());
			}
		}
	}
}

void Plugin::writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const
{
	Q_UNUSED(xmlWriter);
	Q_UNUSED(node);
	throw Exception("cutehmi::modbus::plugin::Plugin::writeXML() not implemented yet.");
}

void Plugin::parseModbus(const xml::ParseHelper & parentHelper, ProjectNode & node, const QString & id, const QString & name)
{
	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("client", 1, 1)
		   << xml::ParseElement("service", 1, 1);

	std::unique_ptr<Client> client;
	std::unique_ptr<Service> service;
	std::unique_ptr<internal::AbstractConnection> connection;
	unsigned long serviceSleep = 0;

	const QXmlStreamReader & xmlReader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "client") {
			xml::ParseHelper clientHelper(& helper);
			clientHelper << xml::ParseElement("connection", {xml::ParseAttribute("type", "TCP|RTU|dummy")}, 1, 1);

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
			xml::ParseHelper serviceHelper(& helper);
			serviceHelper << xml::ParseElement("sleep", 1, 1);

			while (serviceHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "sleep") {
					bool ok;
					serviceSleep = serviceHelper.readElementText().toULong(& ok);
					if (!ok)
						serviceHelper.raiseError(QObject::tr("Could not convert 'sleep' element contents to long integer."));
				}
			}
		}
	}

	if (!xmlReader.hasError()) {
		client.reset(new Client(std::move(connection)));
		service.reset(new Service(name, client.get()));
		service->setSleep(serviceSleep);
		ProjectNode * modbusNode = node.addChild(id, ProjectNodeData(name));
		modbusNode->addExtension(client.get());
		modbusNode->addExtension(service.get());

		if (node.root()->child("cutehmi_services_1")) {
			services::ServiceRegistry * serviceRegistry = qobject_cast<services::ServiceRegistry *>(node.root()->child("cutehmi_services_1")->extension(services::ServiceRegistry::staticMetaObject.className()));
			CUTEHMI_ASSERT(serviceRegistry != nullptr, "pointer must not be nullptr");
			serviceRegistry->add(service.get());
		} else
			CUTEHMI_LOG_WARNING("Plugin 'cutehmi_services_1' not available.");

		modbusNode->data().append(std::unique_ptr<ModbusNodeData>(new ModbusNodeData(std::move(client), std::move(service))));
	}
}

void Plugin::parseTCP(const xml::ParseHelper & parentHelper, std::unique_ptr<internal::AbstractConnection> & connection)
{
	QString name;
	QString service;
	internal::LibmodbusConnection::Timeout byteTimeout;
	internal::LibmodbusConnection::Timeout responseTimeout;
	std::unique_ptr<internal::TCPConnection> tcpConnection;
	int unitId = MODBUS_TCP_SLAVE;

	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("node", 1, 1)
		   << xml::ParseElement("service", 1, 1)
		   << xml::ParseElement("byte_timeout", 1, 1)
		   << xml::ParseElement("response_timeout", 1, 1)
		   << xml::ParseElement("unit_id", 1, 1);

	const QXmlStreamReader & xmlReader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "node")
			name = helper.readElementText();
		else if (xmlReader.name() == "service")
			service = helper.readElementText();
		else if (xmlReader.name() == "byte_timeout") {
			if (!timeoutFromString(helper.readElementText(), byteTimeout))
				helper.raiseError(QObject::tr("Could not parse 'byte_timeout' element."));
		} else if (xmlReader.name() == "response_timeout") {
			if (!timeoutFromString(helper.readElementText(), responseTimeout))
				helper.raiseError(QObject::tr("Could not parse 'response_timeout' element."));
		} else if (xmlReader.name() == "unit_id") {
			bool ok;
			unitId = helper.readElementText().toInt(& ok);
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'unit_id' element contents to integer."));
		}
	}
	tcpConnection.reset(new internal::TCPConnection(name, service, unitId));
	tcpConnection->setByteTimeout(byteTimeout);
	tcpConnection->setResponseTimeout(responseTimeout);
	connection.reset(tcpConnection.release());
}

void Plugin::parseRTU(const xml::ParseHelper & parentHelper, std::unique_ptr<internal::AbstractConnection> & connection)
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

	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("port", 1, 1)
		   << xml::ParseElement("baud_rate", 1, 1)
		   << xml::ParseElement("parity", 1, 1)
		   << xml::ParseElement("data_bits", 1, 1)
		   << xml::ParseElement("stop_bits", 1, 1)
		   << xml::ParseElement("mode", 1, 1)
		   << xml::ParseElement("slave_id", 1, 1);

	const QXmlStreamReader & xmlReader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "port")
			port = helper.readElementText();
		else if (xmlReader.name() == "baud_rate") {
			bool ok;
			baudRate = xmlReader.text().toInt(& ok);
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'baud_rate' element contents to integer."));
		} else if (xmlReader.name() == "parity") {
			QString parityText = helper.readElementText();
			if (parityText == "NONE")
				parity = internal::RTUConnection::Parity::NONE;
			else if (parityText == "ODD")
				parity = internal::RTUConnection::Parity::ODD;
			else if (parityText == "EVEN")
				parity = internal::RTUConnection::Parity::EVEN;
			else
				helper.raiseError(QObject::tr("Contents of 'parity' element must match pattern 'NONE|ODD|EVEN'."));
		} else if (xmlReader.name() == "data_bits") {
			bool ok;
			dataBits = static_cast<internal::RTUConnection::DataBits>(helper.readElementText().toInt(& ok));
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'data_bits' element contents to integer."));
		} else if (xmlReader.name() == "stop_bits") {
			bool ok;
			stopBits = static_cast<internal::RTUConnection::StopBits>(helper.readElementText().toInt(& ok));
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'stop_bits' element contents to integer."));
		} else if (xmlReader.name() == "mode") {
			QString modeText = helper.readElementText();
			if (modeText == "RS232")
				mode = internal::RTUConnection::Mode::RS232;
//<workaround id="cutehmi_modbus_1-1" target="libmodbus" cause="bug">
//			else if (modeText == "RS485")
//				mode = internal::RTUConnection::Mode::RS485;
//</workaround>
			else
				helper.raiseError(QObject::tr("Contents of 'mode' element must match pattern 'RS232'."));
		} else if (xmlReader.name() == "slave_id") {
			bool ok;
			slaveId = helper.readElementText().toInt(& ok);
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'slave_id' element contents to integer."));
		} else if (xmlReader.name() == "byte_timeout") {
			if (!timeoutFromString(helper.readElementText(), byteTimeout))
				helper.raiseError(QObject::tr("Could not parse 'byte_timeout' element."));
		} else if (xmlReader.name() == "response_timeout") {
			if (!timeoutFromString(helper.readElementText(), responseTimeout))
				helper.raiseError(QObject::tr("Could not parse 'response_timeout' element."));
		}
	}

	rtuConnection.reset(new internal::RTUConnection(port, baudRate, parity, dataBits, stopBits, mode, slaveId));
	rtuConnection->setByteTimeout(byteTimeout);
	rtuConnection->setResponseTimeout(responseTimeout);
	connection.reset(rtuConnection.release());
}

void Plugin::parseDummy(const xml::ParseHelper & parentHelper, std::unique_ptr<internal::AbstractConnection> & connection)
{
	unsigned long latency = 0;
	unsigned long connectLatency = 0;
	unsigned long disconnectLatency = 0;
	std::unique_ptr<internal::DummyConnection> dummyConnection;

	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("latency", 1, 1)
		   << xml::ParseElement("connect_latency", 1, 1)
		   << xml::ParseElement("disconnect_latency", 1, 1);

	const QXmlStreamReader & xmlReader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "latency") {
			bool ok;
			latency = helper.readElementText().toULong(& ok);
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'latency' element data to long integer."));
		} else if (xmlReader.name() == "connect_latency") {
			bool ok;
			connectLatency = helper.readElementText().toULong(& ok);
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'connect_latency' element data to long integer."));
		} else if (xmlReader.name() == "disconnect_latency") {
			bool ok;
			disconnectLatency = helper.readElementText().toULong(& ok);
			if (!ok)
				helper.raiseError(QObject::tr("Could not convert 'disconnect_latency' element data to long integer."));
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
		CUTEHMI_LOG_DEBUG("Values smaller than a microsecond will be ignored.");
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
