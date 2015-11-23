#include "RTUConnection.hpp"
#include "Exception.hpp"

#include <QObject>

namespace modbus {

RTUConnection::RTUConnection(const QString & port, int baudRate, Parity parity, DataBits dataBits, StopBits stopBits, Mode mode):
	m_port(port),
	m_baudRate(baudRate),
	m_parity(parity),
	m_dataBits(dataBits),
	m_stopBits(stopBits),
	m_mode(mode),
	m_connected(false)
{
	//translate Parity enum to char used by libmodbus
	char libmodbusParity;
	switch (parity) {
		case Parity::EVEN:
			libmodbusParity = 'E';
			break;
		case Parity::ODD:
			libmodbusParity = 'O';
			break;
		default:
			libmodbusParity = 'N';
	}
	m_context =  modbus_new_rtu(port.toLocal8Bit().data(), baudRate, libmodbusParity, static_cast<int>(dataBits), static_cast<int>(stopBits));
	if (m_context == NULL) {
		QString title = QObject::tr("Unable to create connection.");
		switch (errno) {
			case EINVAL:
				throw Exception(title, QObject::tr("Unable to create a connection for the port: %1. One of the parameters is incorrect.").arg(m_port));
			default:
				throw Exception(title, QObject::tr("Unable to create a connection for the port: %1.").arg(m_port));
		}
	}
	if (modbus_rtu_set_serial_mode(m_context, static_cast<int>(mode)) == -1) {
		try {
			QString title = QObject::tr("Failed to set serial port mode.");
			switch (errno) {
				case EINVAL:
					throw Exception(title, QObject::tr("Connection context is not RTU."));
				case ENOTSUP:
					throw Exception(title, QObject::tr("Function is not supported on this platform."));
				default:
					throw Exception(title, QObject::tr("Unrecognized error code."));
			}
		} catch (...) {
			modbus_free(m_context);
			m_context = NULL;
			throw;
		}
	}
}

RTUConnection::~RTUConnection()
{
	if (m_context != NULL)
		modbus_free(m_context);
}

void RTUConnection::connect()
{
	if (m_connected)
		return;
	if (m_context == NULL)
		throw Exception(QObject::tr("Unable to connect."), QObject::tr("Connection has not been properly configured."));
	if (modbus_connect(m_context) == 0)
		m_connected = true;
	else
		throw Exception(QObject::tr("Unable to connect."), QObject::tr("Can not connect to the device using port: %1.").arg(m_port));
}

void RTUConnection::disconnect()
{
	modbus_close(m_context);
	m_connected = false;
}

bool RTUConnection::connected() const
{
	return m_connected;
}

}

