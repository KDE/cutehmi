#include "RTUConnection.hpp"
#include "Exception.hpp"

#include <QObject>

namespace cutehmi {
namespace modbus {

RTUConnection::RTUConnection(const QString & port, int baudRate, Parity parity, DataBits dataBits, StopBits stopBits, Mode mode, int slaveId):
	Parent(modbus_new_rtu(port.toLocal8Bit().data(), baudRate, ToLibmodbusParity(parity), static_cast<int>(dataBits), static_cast<int>(stopBits))),
	m_port(port),
	m_baudRate(baudRate),
	m_parity(parity),
	m_dataBits(dataBits),
	m_stopBits(stopBits),
	m_mode(mode),
	m_slaveId(slaveId)
{
	if (context() == NULL) {
		switch (errno) {
			case EINVAL:
				throw Exception(QObject::tr("Unable to create a connection for the port: %1. One of the parameters is incorrect.").arg(m_port));
			default:
				throw Exception(QObject::tr("Unable to create a connection for the port: %1.").arg(m_port));
		}
	}

	modbus_set_slave(context(), m_slaveId);

//<workaround id="LibModbus-1" target="libmodbus" cause="bug">
//	if (modbus_rtu_set_serial_mode(context(), static_cast<int>(mode)) == -1) {
//		try {
//			QString title = QObject::tr("Failed to set serial port mode.");
//			switch (errno) {
//				case EINVAL:
//					throw Exception(title, QObject::tr("Connection context is not RTU."));
//				case ENOTSUP:
//					throw Exception(title, QObject::tr("Function is not supported on this platform."));
//				default:
//					throw Exception(title, QObject::tr("Unrecognized error code."));
//			}
//		} catch (...) {
//			modbus_free(context());
//			setContext(NULL);
//			throw;
//		}
//	}
//</workaround>
}

RTUConnection::~RTUConnection()
{
	modbus_free(context());
}

const QString & RTUConnection::port() const
{
	return m_port;
}

int RTUConnection::baudRate() const
{
	return m_baudRate;
}

RTUConnection::Parity RTUConnection::parity() const
{
	return m_parity;
}

RTUConnection::DataBits RTUConnection::dataBits() const
{
	return m_dataBits;
}

RTUConnection::StopBits RTUConnection::stopBits() const
{
	return m_stopBits;
}

RTUConnection::Mode RTUConnection::mode() const
{
	return m_mode;
}

int RTUConnection::slaveId() const
{
	return m_slaveId;
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
			qFatal("Unrecognized parity code: %d.", static_cast<int>(parity));
	}
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
