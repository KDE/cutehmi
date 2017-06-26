#include "macros.hpp"
#include "Plugin.hpp"
#include "PluginNodeData.hpp"
#include "ModbusNodeData.hpp"

#include <modbus/internal/TCPConnection.hpp>
#include <modbus/internal/RTUConnection.hpp>
#include <modbus/internal/DummyConnection.hpp>

#include <services/ServiceRegistry.hpp>

#include <base/XMLBackendPlugin.hpp>
#include <base/xml/ParseHelper.hpp>
#include <base/Exception.hpp>

#include <QtDebug>

namespace cutehmi {
namespace modbus {
namespace plugin {

constexpr const char * Plugin::NAMESPACE_URI;

void Plugin::init(base::ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
	node.addExtension(pluginNodeData->xmlBackendPlugin());
	node.data().append(std::move(pluginNodeData));
}

void Plugin::readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node)
{
	CUTEHMI_MODBUS_PLUGIN_QDEBUG("Plugin cutehmi.modbus starts parsing its own portion of document...");

	base::xml::ParseHelper helper(& xmlReader, NAMESPACE_URI);
	helper << base::xml::ParseElement("cutehmi_plugin_modbus", 1, 1);

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "cutehmi_plugin_modbus") {
			base::xml::ParseHelper nodeHelper(& xmlReader, NAMESPACE_URI);
			nodeHelper << base::xml::ParseElement("modbus", {base::xml::ParseAttribute("id"),
															 base::xml::ParseAttribute("name")}, 0);
			while (nodeHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "modbus")
					parseModbus(xmlReader, node, xmlReader.attributes().value("id").toString(), xmlReader.attributes().value("name").toString());
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

void Plugin::parseModbus(QXmlStreamReader & xmlReader, base::ProjectNode & node, const QString & id, const QString & name)
{
	base::xml::ParseHelper helper(& xmlReader, NAMESPACE_URI);
	helper << base::xml::ParseElement("client", 1, 1)
		   << base::xml::ParseElement("service", 1, 1);

	std::unique_ptr<Client> client;
	std::unique_ptr<Service> service;
	std::unique_ptr<internal::AbstractConnection> connection;
	unsigned long serviceSleep = 0;

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "client") {
			base::xml::ParseHelper clientHelper(& xmlReader, NAMESPACE_URI);
			clientHelper << base::xml::ParseElement("connection", {base::xml::ParseAttribute("type", "TCP|RTU|dummy")}, 1, 1);

			while (clientHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "connection") {
					if (xmlReader.attributes().value("type") == "TCP")
						parseTCP(xmlReader, connection);
					else if (xmlReader.attributes().value("type") == "RTU")
						parseRTU(xmlReader, connection);
					else if (xmlReader.attributes().value("type") == "dummy")
						parseDummy(xmlReader, connection);
				}
			}
		} else if (xmlReader.name() == "service") {
			base::xml::ParseHelper serviceHelper(& xmlReader, NAMESPACE_URI);
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

	if (node.root()->child("cutehmi.services")) {
		services::ServiceRegistry * serviceRegistry = qobject_cast<services::ServiceRegistry *>(node.root()->child("cutehmi.services")->extension(services::ServiceRegistry::staticMetaObject.className()));
		CUTEHMI_BASE_ASSERT(serviceRegistry != nullptr, "pointer must not be nullptr");
		serviceRegistry->add(service.get());
	} else
		CUTEHMI_MODBUS_PLUGIN_QWARNING("Extension 'cutehmi.services' not available.");

	modbusNode->data().append(std::unique_ptr<ModbusNodeData>(new ModbusNodeData(std::move(client), std::move(service))));
}

void Plugin::parseTCP(QXmlStreamReader & xmlReader, std::unique_ptr<internal::AbstractConnection> & connection)
{
	QString name;
	QString service;
	internal::LibmodbusConnection::Timeout byteTimeout;
	internal::LibmodbusConnection::Timeout responseTimeout;
	std::unique_ptr<internal::TCPConnection> tcpConnection;
	int unitId = MODBUS_TCP_SLAVE;

	base::xml::ParseHelper helper(& xmlReader, NAMESPACE_URI);
	helper << base::xml::ParseElement("node", 1, 1)
		   << base::xml::ParseElement("service", 1, 1)
		   << base::xml::ParseElement("byte_timeout", 1, 1)
		   << base::xml::ParseElement("response_timeout", 1, 1)
		   << base::xml::ParseElement("unit_id", 1, 1);

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

void Plugin::parseRTU(QXmlStreamReader & xmlReader, std::unique_ptr<internal::AbstractConnection> & connection)
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

	base::xml::ParseHelper helper(& xmlReader, NAMESPACE_URI);
	helper << base::xml::ParseElement("port", 1, 1)
		   << base::xml::ParseElement("baud_rate", 1, 1)
		   << base::xml::ParseElement("parity", 1, 1)
		   << base::xml::ParseElement("data_bits", 1, 1)
		   << base::xml::ParseElement("stop_bits", 1, 1)
		   << base::xml::ParseElement("mode", 1, 1)
		   << base::xml::ParseElement("slave_id", 1, 1);

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
//<workaround id="LibModbus-1" target="libmodbus" cause="bug">
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

void Plugin::parseDummy(QXmlStreamReader & xmlReader, std::unique_ptr<internal::AbstractConnection> & connection)
{
	unsigned long latency = 0;
	unsigned long connectLatency = 0;
	unsigned long disconnectLatency = 0;
	std::unique_ptr<internal::DummyConnection> dummyConnection;

	base::xml::ParseHelper helper(& xmlReader, NAMESPACE_URI);
	helper << base::xml::ParseElement("latency", 1, 1)
		   << base::xml::ParseElement("connect_latency", 1, 1)
		   << base::xml::ParseElement("disconnect_latency", 1, 1);

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


//base::Error Plugin::readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node)
//{
//	unsigned long serviceSleep = 0;

//	qDebug("Plugin cutehmi.modbus starts parsing its own portion of document...");
//	base::ProjectNode * modbusNode = node.addChild(base::ProjectNode::Data("Modbus"), false);
//	while (xmlReader.readNextStartElement()) {
//		if (xmlReader.name() == "plugin_modbus_data") {
//			while (xmlReader.readNextStartElement()) {
//				if (xmlReader.name() == "client") {
//					QString id = xmlReader.attributes().value("id").toString();
//					std::unique_ptr<modbus::AbstractConnection> connection;
//					while (xmlReader.readNextStartElement()) {
//						if (xmlReader.name() == "connection") {
//							if (xmlReader.attributes().value("type") == "TCP") {
//								if (!tcpConnectionFromXML(xmlReader, connection))
//									return base::Error::FAIL;
//							} else if (xmlReader.attributes().value("type") == "RTU") {
//								if (!rtuConnectionFromXML(xmlReader, connection))
//									return base::Error::FAIL;
//							} else if (xmlReader.attributes().value("type") == "dummy") {
//								if (!dummyConnectionFromXML(xmlReader, connection))
//									return base::Error::FAIL;
//							} else
//								return base::Error::FAIL;
//						} else if (xmlReader.name() == "service") {
//							while (xmlReader.readNextStartElement()) {
//								if (xmlReader.name() == "sleep") {
//									if (xmlReader.readNext() != QXmlStreamReader::Characters)
//										return base::Error::FAIL;
//									bool ok;
//									serviceSleep = xmlReader.text().toULong(& ok);
//									if (!ok)
//										return base::Error::FAIL;
//								}
//								xmlReader.skipCurrentElement();	// None of the child elements uses readNextStartElement(). Either readNextStartElement() or skipCurrentElement() must be called for each tag.
//							}
//						} else {
//							qWarning() << "Unrecognized token: " << xmlReader.tokenString();
//							xmlReader.skipCurrentElement();
//						}
//					}
//					std::unique_ptr<modbus::Client> client(new modbus::Client(std::move(connection)));
//					std::unique_ptr<modbus::Service> service(new modbus::Service(QStringLiteral("CuteHMI Modbus (") + id + ")", client.get()));
//					service->setSleep(serviceSleep);
//					std::unique_ptr<modbus::NodeDataObject> dataObject(new modbus::NodeDataObject(std::move(client), std::move(service)));
//					base::ProjectNode * clientNode = modbusNode->addChild(base::ProjectNode::Data(id, std::move(dataObject)));
//					clientNode->setVisitorDelegate(std::unique_ptr<base::ProjectNode::VisitorDelegate>(new modbus::VisitorDelegate(clientNode)));
//				} else
//					xmlReader.skipCurrentElement();
//			}
//		} else
//			xmlReader.skipCurrentElement();
//	}
//	return base::Error::OK;
//}

//base::Error Plugin::writeXML(QXmlStreamWriter & xmlWriter, base::ProjectNode & node) const
//{
//	Q_UNUSED(xmlWriter);
//	Q_UNUSED(node);
//	return base::Error::FAIL;
//}

//base::Error Plugin::dummyConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection)
//{
//	unsigned long latency = 0;
//	modbus::DummyConnection * dummyConnection;

//	while (xmlReader.readNextStartElement()) {
//		if (xmlReader.name() == "latency") {
//			if (xmlReader.readNext() != QXmlStreamReader::Characters)
//				return base::Error::FAIL;
//			bool ok;
//			latency = xmlReader.text().toULong(& ok);
//			if (!ok)
//				return base::Error::FAIL;
//		}
//		xmlReader.skipCurrentElement();	// None of the child elements uses readNextStartElement(). Either readNextStartElement() or skipCurrentElement() must be called for each tag.
//	}
//	dummyConnection = new modbus::DummyConnection;
//	dummyConnection->setLatency(latency);
//	connection.reset(dummyConnection);
//	return base::Error::OK;
//}

//base::Error Plugin::tcpConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection)
//{
//	QString name;
//	QString service;
//	modbus::LibmodbusConnection::Timeout byteTimeout;
//	modbus::LibmodbusConnection::Timeout responseTimeout;
//	modbus::TCPConnection * tcpConnection;

//	while (xmlReader.readNextStartElement()) {
//		if (xmlReader.name() == "node") {
//			if (xmlReader.readNext() != QXmlStreamReader::Characters)
//				return base::Error::FAIL;
//			name = xmlReader.text().toString();
//		} else if (xmlReader.name() == "service") {
//			if (xmlReader.readNext() != QXmlStreamReader::Characters)
//				return base::Error::FAIL;
//			service = xmlReader.text().toString();
//		} else if (!connectionTimeoutsFromXML(xmlReader, byteTimeout, responseTimeout))
//			return base::Error::FAIL;
//		xmlReader.skipCurrentElement();	// None of the child elements uses readNextStartElement(). Either readNextStartElement() or skipCurrentElement() must be called for each tag.
//	}
//	try {
//		tcpConnection = new modbus::TCPConnection(name, service);
//	} catch (modbus::Exception & e) {
//		qDebug(e.what());
//		return base::Error::FAIL;
//	}
//	tcpConnection->setByteTimeout(byteTimeout);
//	tcpConnection->setResponseTimeout(responseTimeout);
//	connection.reset(tcpConnection);
//	return base::Error::OK;
//}

//base::Error Plugin::rtuConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection)
//{
//	QString port;
//	int baudRate = 19200;
//	modbus::RTUConnection::Parity parity = modbus::RTUConnection::Parity::NONE;
//	modbus::RTUConnection::DataBits dataBits = modbus::RTUConnection::DataBits::BITS_8;
//	modbus::RTUConnection::StopBits stopBits = modbus::RTUConnection::StopBits::BITS_1;
//	modbus::RTUConnection::Mode mode = modbus::RTUConnection::Mode::RS232;
//	int slaveId = 0;
//	modbus::LibmodbusConnection::Timeout byteTimeout;
//	modbus::LibmodbusConnection::Timeout responseTimeout;
//	modbus::RTUConnection * rtuConnection;

//	while (xmlReader.readNextStartElement()) {
//		if (xmlReader.name() == "port") {
//			if (xmlReader.readNext() != QXmlStreamReader::Characters)
//				return base::Error::FAIL;
//			port = xmlReader.text().toString();
//		} else if (xmlReader.name() == "baud_rate") {
//			if (xmlReader.readNext() != QXmlStreamReader::Characters)
//				return base::Error::FAIL;
//			bool ok;
//			baudRate = xmlReader.text().toInt(& ok);
//			if (!ok)
//				return base::Error::FAIL;
//		} else if (xmlReader.name() == "parity") {
//			if (xmlReader.readNext() != QXmlStreamReader::Characters)
//				return base::Error::FAIL;
//			if (xmlReader.text().toString() == "NONE")
//				parity = modbus::RTUConnection::Parity::NONE;
//			else if (xmlReader.text().toString() == "ODD")
//				parity = modbus::RTUConnection::Parity::ODD;
//			else if (xmlReader.text().toString() == "EVEN")
//				parity = modbus::RTUConnection::Parity::EVEN;
//			else
//				return base::Error::FAIL;
//		} else if (xmlReader.name() == "data_bits") {
//			if (xmlReader.readNext() != QXmlStreamReader::Characters)
//				return base::Error::FAIL;
//			bool ok;
//			dataBits = static_cast<modbus::RTUConnection::DataBits>(xmlReader.text().toInt(& ok));
//			if (!ok)
//				return base::Error::FAIL;
//		} else if (xmlReader.name() == "stop_bits") {
//			if (xmlReader.readNext() != QXmlStreamReader::Characters)
//				return base::Error::FAIL;
//			bool ok;
//			stopBits = static_cast<modbus::RTUConnection::StopBits>(xmlReader.text().toInt(& ok));
//			if (!ok)
//				return base::Error::FAIL;
//		} else if (xmlReader.name() == "mode") {
//			if (xmlReader.readNext() != QXmlStreamReader::Characters)
//				return base::Error::FAIL;
//			if (xmlReader.text().toString() == "RS232")
//				mode = modbus::RTUConnection::Mode::RS232;
////<workaround id="LibModbus-1" target="libmodbus" cause="bug">
////			else if (xmlReader.text().toString() == "RS485")
////				mode = modbus::RTUConnection::Mode::RS485;
////</workaround>
//			else
//				return base::Error::FAIL;
//		} else if (xmlReader.name() == "slave_id") {
//				if (xmlReader.readNext() != QXmlStreamReader::Characters)
//					return base::Error::FAIL;
//				bool ok;
//				slaveId = xmlReader.text().toInt(& ok);
//				if (!ok)
//					return base::Error::FAIL;
//		} else if (!connectionTimeoutsFromXML(xmlReader, byteTimeout, responseTimeout))
//			return base::Error::FAIL;
//		xmlReader.skipCurrentElement();	// None of the child elements uses readNextStartElement(). Either readNextStartElement() or skipCurrentElement() must be called for each tag.
//	}
//	try {
//		rtuConnection = new modbus::RTUConnection(port, baudRate, parity, dataBits, stopBits, mode, slaveId);
//	} catch (modbus::Exception & e) {
//		qDebug(e.what());
//		return base::Error::FAIL;
//	}
//	rtuConnection->setByteTimeout(byteTimeout);
//	rtuConnection->setResponseTimeout(responseTimeout);
//	connection.reset(rtuConnection);
//	return base::Error::OK;
//}

//base::Error Plugin::connectionTimeoutsFromXML(QXmlStreamReader & xmlReader, modbus::LibmodbusConnection::Timeout & byteTimeout, modbus::LibmodbusConnection::Timeout & responseTimeout)
//{
//	if (xmlReader.name() == "byte_timeout") {
//		if (xmlReader.readNext() != QXmlStreamReader::Characters)
//			return base::Error::FAIL;
//		return timeoutFromString(xmlReader.text().toString(), byteTimeout);
//	} else if (xmlReader.name() == "response_timeout") {
//		if (xmlReader.readNext() != QXmlStreamReader::Characters)
//			return base::Error::FAIL;
//		return timeoutFromString(xmlReader.text().toString(), responseTimeout);
//	}
//	return base::Error::OK;
//}

//base::Error Plugin::timeoutFromString(const QString & timeoutString, modbus::LibmodbusConnection::Timeout & timeout)
//{
//	unsigned long sec, usec;
//	base::Error result = secUsecFromString(timeoutString, sec, usec);
//	// unsigned long is guaranteed to be at least 32 bit.
//	timeout.sec = sec;
//	timeout.usec = usec;
//	return result;
//}

//base::Error Plugin::secUsecFromString(const QString & timeoutString, unsigned long & sec, unsigned long & usec)
//{
//	bool okSec, okUsec;

//	QStringList secUsec = timeoutString.split(".");
//	if (secUsec.length() != 2)
//		return base::Error::FAIL;
//	if (secUsec.value(1).count() > 6)
//		qDebug("Values smaller than a microsecond will be ignored.");

//	sec = secUsec.value(0).toULong(& okSec);
//	usec = secUsec.value(1).leftJustified(6, '0', true).toULong(& okUsec); // unsigned long is guaranteed to be at least 32 bit.

//	if (!okSec || !okUsec)
//		return base::Error::FAIL;
//	return base::Error::OK;
//}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
