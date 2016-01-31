#include "RTUConnection.hpp"
#include "Exception.hpp"

#include <QObject>

namespace modbus {

RTUConnection_baseFromMember::RTUConnection_baseFromMember(const QString & port, int baudRate, Parity parity, DataBits dataBits, StopBits stopBits):
	m_port(port),
	m_baudRate(baudRate),
	m_parity(parity),
	m_dataBits(dataBits),
	m_stopBits(stopBits)
{
}


RTUConnection::RTUConnection(const QString & port, int baudRate, Parity parity, DataBits dataBits, StopBits stopBits, Mode mode):
	RTUConnection_baseFromMember(port, baudRate, parity, dataBits, stopBits),
	Parent(modbus_new_rtu(port.toLocal8Bit().data(), baudRate, ToLibmodbusParity(parity), static_cast<int>(dataBits), static_cast<int>(stopBits))),
	m_mode(mode)
{
	if (context() == NULL) {
		QString title = QObject::tr("Unable to create connection.");
		switch (errno) {
			case EINVAL:
				throw Exception(title, QObject::tr("Unable to create a connection for the port: %1. One of the parameters is incorrect.").arg(m_port));
			default:
				throw Exception(title, QObject::tr("Unable to create a connection for the port: %1.").arg(m_port));
		}
	}
	connect();
	if (modbus_rtu_set_serial_mode(context(), static_cast<int>(mode)) == -1) {
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
			modbus_free(context());
			setContext(NULL);
			throw;
		}
	}
}

RTUConnection::~RTUConnection()
{
	if (context() != NULL)
		modbus_free(context());
}

char RTUConnection::ToLibmodbusParity(Parity parity)
{
	//translate Parity enum to char used by libmodbus
	switch (parity) {
		case Parity::EVEN:
			return 'E';
		case Parity::ODD:
			return 'O';
		case Parity::NONE:
			return 'N';
		default:
			qFatal("Unrecognized parity code: %d.", parity);
	}
}

}

