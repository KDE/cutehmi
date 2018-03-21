#include "../../../../include/cutehmi/modbus/internal/RTUConnection.hpp"
#include "../../../../include/cutehmi/modbus/Exception.hpp"

#include <QObject>

namespace cutehmi {
namespace modbus {
namespace internal {

RTUConnection::RTUConnection(const QString & port, int baudRate, Parity parity, DataBits dataBits, StopBits stopBits, Mode mode, int slaveId) noexcept(false):
	Parent(modbus_new_rtu(port.toLocal8Bit().data(), baudRate, ToLibmodbusParity(parity), static_cast<int>(dataBits), static_cast<int>(stopBits))),
	m(new Members{port, baudRate, parity, dataBits, stopBits, mode, slaveId})
{
	if (context() == NULL) {
		switch (errno) {
			case EINVAL:
				throw Exception(QObject::tr("Unable to create a connection for the port '%1'. One of the parameters is incorrect.").arg(m->port));
			default:
				throw Exception(QObject::tr("Unable to create a connection for the port '%1'.").arg(m->port));
		}
	}

	modbus_set_slave(context(), m->slaveId);

//<workaround id="cutehmi_modbus_1-1" target="libmodbus" cause="bug">
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
	return m->port;
}

int RTUConnection::baudRate() const
{
	return m->baudRate;
}

RTUConnection::Parity RTUConnection::parity() const
{
	return m->parity;
}

RTUConnection::DataBits RTUConnection::dataBits() const
{
	return m->dataBits;
}

RTUConnection::StopBits RTUConnection::stopBits() const
{
	return m->stopBits;
}

RTUConnection::Mode RTUConnection::mode() const
{
	return m->mode;
}

int RTUConnection::slaveId() const
{
	return m->slaveId;
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
			throw Exception(QObject::tr("Unrecognized parity code ('%1').").arg(static_cast<int>(parity)));
	}
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
