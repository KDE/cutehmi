#include "../../../include/modbus/internal/LibmodbusConnection.hpp"
#include "../../../include/modbus/internal/functions.hpp"

#include <QtDebug>

namespace cutehmi {
namespace modbus {
namespace internal {

void LibmodbusConnection::setByteTimeout(Timeout timeout)
{
	 if (modbus_set_byte_timeout(context(), timeout.sec, timeout.usec) == -1)
		 CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
}

LibmodbusConnection::Timeout LibmodbusConnection::byteTimeout() const
{
	Timeout timeout;
	// libmodbus seems to be not const-correct.
	if (modbus_get_byte_timeout(const_cast<modbus_t *>(context()), & timeout.sec, & timeout.usec) == -1)
		CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
	return timeout;
}

void LibmodbusConnection::setResponseTimeout(Timeout timeout)
{
	 if (modbus_set_response_timeout(context(), timeout.sec, timeout.usec) == -1)
		 CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
}

LibmodbusConnection::Timeout LibmodbusConnection::responseTimeout() const
{
	Timeout timeout;
	// libmodbus seems to be not const-correct.
	if (modbus_get_response_timeout(const_cast<modbus_t *>(context()), & timeout.sec, & timeout.usec) == -1)
		CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
	return timeout;
}

bool LibmodbusConnection::connect()
{
	m->connected = modbus_connect(context()) == 0;
	return m->connected;
}

void LibmodbusConnection::disconnect()
{
	modbus_close(context());
	m->connected = false;
}

bool LibmodbusConnection::connected() const
{
	return m->connected;
}

int LibmodbusConnection::readIr(int addr, int num, uint16_t * dest)
{
	QMutexLocker locker(& LibmodbusConnection::Mutex());
	// libmodbus seems to take care about endianness.
	int result = modbus_read_input_registers(context(), addr, num, dest);
	if (result == -1)
		CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
	return result;
}

int LibmodbusConnection::readR(int addr, int num, uint16_t * dest)
{
	QMutexLocker locker(& LibmodbusConnection::Mutex());
	// libmodbus seems to take care about endianness.
	int result = modbus_read_registers(context(), addr, num, dest);
	if (result == -1)
		CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
	return result;
}

int LibmodbusConnection::writeR(int addr, uint16_t value)
{
	QMutexLocker locker(& LibmodbusConnection::Mutex());
	// libmodbus seems to take care about endianness.
	// For some reason libmodbus uses int as a value parameter, so we need to convert it back.
	int result = modbus_write_register(context(), addr, intFromUint16(value));
	if (result != 1)
		CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
	return result;
}

int LibmodbusConnection::readIb(int addr, int num, bool * dest)
{
	QMutexLocker locker(& LibmodbusConnection::Mutex());
	m->bIbBuffer.reserve(num);
	int result = modbus_read_input_bits(context(), addr, num, & m->bIbBuffer[0]);
	if (result == -1)
		CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
	for (int i = 0; i < result; i++)
		dest[i] = m->bIbBuffer[i];
	return result;
}

int LibmodbusConnection::readB(int addr, int num, bool * dest)
{
	QMutexLocker locker(& LibmodbusConnection::Mutex());
	m->bIbBuffer.reserve(num);
	int result = modbus_read_bits(context(), addr, num, & m->bIbBuffer[0]);
	if (result == -1)
		CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
	for (int i = 0; i < result; i++)
		dest[i] = m->bIbBuffer[i];
	return result;
}

int LibmodbusConnection::writeB(int addr, bool value)
{
	QMutexLocker locker(& LibmodbusConnection::Mutex());
	// "If the source type is bool, the value false is converted to zero and the value true is converted to one."
	//		-- §4.7/4 C++ Standard via StackOverflow.
	int result = modbus_write_bit(context(), addr, value);
	if (result == -1)
		CUTEHMI_LOG_DEBUG("libmodbus error: " << modbus_strerror(errno) << ".");
	return result;
}

LibmodbusConnection::LibmodbusConnection(modbus_t * context):
	m(new Members(context))
{
}

const modbus_t * LibmodbusConnection::context() const
{
	return m->context;
}

modbus_t * LibmodbusConnection::context()
{
	return m->context;
}

void LibmodbusConnection::setContext(modbus_t * context)
{
	m->context = context;
}

QMutex & LibmodbusConnection::Mutex()
{
	static QMutex mutex;
	return mutex;
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
