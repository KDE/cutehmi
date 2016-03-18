#include "AbstractConnection.hpp"
#include "functions.hpp"

#include <QtDebug>

namespace cutehmi {
namespace modbus {

void AbstractConnection::setByteTimeout(Timeout timeout)
{
	 if (modbus_set_byte_timeout(context(), timeout.sec, timeout.usec) == -1)
		 qDebug() << "libmodbus error: " << modbus_strerror(errno);
}

AbstractConnection::Timeout AbstractConnection::byteTimeout() const
{
	Timeout timeout;
	// libmodbus seems to be not const-correct.
	if (modbus_get_byte_timeout(const_cast<modbus_t *>(context()), & timeout.sec, & timeout.usec) == -1)
		qDebug() << "libmodbus error: " << modbus_strerror(errno);
	return timeout;
}

void AbstractConnection::setResponseTimeout(Timeout timeout)
{
	 if (modbus_set_response_timeout(context(), timeout.sec, timeout.usec) == -1)
		 qDebug() << "libmodbus error: " << modbus_strerror(errno);
}

AbstractConnection::Timeout AbstractConnection::responseTimeout() const
{
	Timeout timeout;
	// libmodbus seems to be not const-correct.
	if (modbus_get_response_timeout(const_cast<modbus_t *>(context()), & timeout.sec, & timeout.usec) == -1)
		qDebug() << "libmodbus error: " << modbus_strerror(errno);
	return timeout;
}

bool AbstractConnection::connected() const
{
	return m_connected;
}

void AbstractConnection::connect()
{
	if (connected())
		return;
	if (modbus_connect(context()) == 0)
		setConnected(true);
	else
		qDebug("Unable to connect.");
}

void AbstractConnection::disconnect()
{
	modbus_close(context());
	setConnected(false);
}

int AbstractConnection::readIr(int addr, int num, uint16_t & dest)
{
	int result = modbus_read_input_registers(context(), addr, num, & dest);
	if (result != num)
		qDebug() << "libmodbus error: " << modbus_strerror(errno);
	return result;
}

int AbstractConnection::readR(int addr, int num, uint16_t & dest)
{
	int result = modbus_read_registers(context(), addr, num, & dest);
	if (result != num)
		qDebug() << "libmodbus error: " << modbus_strerror(errno);
	return result;
}

int AbstractConnection::writeR(int addr, uint16_t value)
{
	// For some reason libmodbus uses int as a value parameter, so we need to convert it back.
	int result = modbus_write_register(context(), addr, intFromUint16(value));
	if (result != 1)
		qDebug() << "libmodbus error: " << modbus_strerror(errno);
	return result;
}

AbstractConnection::AbstractConnection(modbus_t * context):
	m_context(context),
	m_connected(false)
{
}

const modbus_t * AbstractConnection::context() const
{
	return m_context;
}

modbus_t * AbstractConnection::context()
{
	return m_context;
}

void AbstractConnection::setContext(modbus_t * context)
{
	m_context = context;
}

void AbstractConnection::setConnected(bool connected)
{
	m_connected = connected;
}


}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
