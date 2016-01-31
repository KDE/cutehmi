#include "Plugin.hpp"

#include <modbus/TCPConnection.hpp>
#include <modbus/RTUConnection.hpp>
#include <modbus/Client.hpp>

#include <QtDebug>

namespace pluginModbus {

base::Error Plugin::readXML(QXmlStreamReader & xmlReader, base::ProjectModel::Node & node)
{
	qDebug("CuteHMI.PluginModbus starts parsing own portion of document...");
	base::ProjectModel::Node * modbusNode = node.createChild(base::ProjectModel::Node::Data("Modbus"), false);
	while (xmlReader.readNextStartElement()) {
		if (xmlReader.name() == "plugin_modbus_data") {
			while (xmlReader.readNextStartElement()) {
				if (xmlReader.name() == "client") {
					QString id = xmlReader.attributes().value("id").toString();
					std::unique_ptr<modbus::AbstractConnection> connection;
					while (xmlReader.readNextStartElement()) {
						if (xmlReader.name() == "connection") {
							if (xmlReader.attributes().value("type") == "TCP") {
								if (!tcpConnectionFromXML(xmlReader, connection).success())
									return base::Error::FAIL;
							} else if (xmlReader.attributes().value("type") == "RTU") {
								if (!rtuConnectionFromXML(xmlReader, connection).success())
									return base::Error::FAIL;
							}
						} else
							xmlReader.skipCurrentElement();
					}
					modbus::Client * client = new modbus::Client(std::move(connection));
					modbusNode->createChild(base::ProjectModel::Node::Data(id, client));
				} else
					xmlReader.skipCurrentElement();
			}
		} else
			xmlReader.skipCurrentElement();
	}
	return base::Error::OK;
}

base::Error Plugin::writeXML(QXmlStreamWriter & xmlWriter) const
{
	Q_UNUSED(xmlWriter);
	return base::Error::FAIL;
}

base::Error Plugin::tcpConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection)
{
	QString name;
	QString service;
	while (xmlReader.readNextStartElement()) {
		if (xmlReader.name() == "node") {
			if (xmlReader.readNext() != QXmlStreamReader::Characters)
				return base::Error::FAIL;
			name = xmlReader.text().toString();
		} else if (xmlReader.name() == "service") {
			if (xmlReader.readNext() != QXmlStreamReader::Characters)
				return base::Error::FAIL;
			service = xmlReader.text().toString();
		}
		xmlReader.skipCurrentElement();	// None of the child elements uses readNextStartElement(). Either readNextStartElement() or skipCurrentElement() must be called for each tag.
	}
	connection.reset(new modbus::TCPConnection(name, service));
	return base::Error::OK;
}

base::Error Plugin::rtuConnectionFromXML(QXmlStreamReader & xmlReader, std::unique_ptr<modbus::AbstractConnection> & connection)
{
	QString port;
	int baudRate = 19200;
	modbus::RTUConnection::Parity parity = modbus::RTUConnection::Parity::NONE;
	modbus::RTUConnection::DataBits dataBits = modbus::RTUConnection::DataBits::BITS_8;
	modbus::RTUConnection::StopBits stopBits = modbus::RTUConnection::StopBits::BITS_1;
	modbus::RTUConnection::Mode mode = modbus::RTUConnection::Mode::RS232;

	while (xmlReader.readNextStartElement()) {
		if (xmlReader.name() == "port") {
			if (xmlReader.readNext() != QXmlStreamReader::Characters)
				return base::Error::FAIL;
			port = xmlReader.text().toString();
		} else if (xmlReader.name() == "baudRate") {
			if (xmlReader.readNext() != QXmlStreamReader::Characters)
				return base::Error::FAIL;
			bool ok;
			baudRate = xmlReader.text().toInt(& ok);
			if (!ok)
				return base::Error::FAIL;
		} else if (xmlReader.name() == "parity") {
			if (xmlReader.readNext() != QXmlStreamReader::Characters)
				return base::Error::FAIL;
			if (xmlReader.text().toString() == "NONE")
				parity = modbus::RTUConnection::Parity::NONE;
			else if (xmlReader.text().toString() == "ODD")
				parity = modbus::RTUConnection::Parity::ODD;
			else if (xmlReader.text().toString() == "EVEN")
				parity = modbus::RTUConnection::Parity::EVEN;
			else
				return base::Error::FAIL;
		} else if (xmlReader.name() == "data_bits") {
			if (xmlReader.readNext() != QXmlStreamReader::Characters)
				return base::Error::FAIL;
			bool ok;
			dataBits = static_cast<modbus::RTUConnection::DataBits>(xmlReader.text().toInt(& ok));
			if (!ok)
				return base::Error::FAIL;

		} else if (xmlReader.name() == "stop_bits") {
			if (xmlReader.readNext() != QXmlStreamReader::Characters)
				return base::Error::FAIL;
			bool ok;
			stopBits = static_cast<modbus::RTUConnection::StopBits>(xmlReader.text().toInt(& ok));
			if (!ok)
				return base::Error::FAIL;
		} else if (xmlReader.name() == "mode") {
			if (xmlReader.readNext() != QXmlStreamReader::Characters)
				return base::Error::FAIL;
			if (xmlReader.text().toString() == "RS232")
				mode = modbus::RTUConnection::Mode::RS232;
			else if (xmlReader.text().toString() == "RS485")
				mode = modbus::RTUConnection::Mode::RS485;
			else
				return base::Error::FAIL;
		}
		xmlReader.skipCurrentElement();	// None of the child elements uses readNextStartElement(). Either readNextStartElement() or skipCurrentElement() must be called for each tag.
	}
	connection.reset(new modbus::RTUConnection(port, baudRate, parity, dataBits, stopBits, mode));
	return base::Error::OK;
}

}
