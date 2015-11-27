#include "AbstractConnection.hpp"

namespace modbus {

bool AbstractConnection::connected() const
{
	return m_connected;
}

void AbstractConnection::connect()
{
	if (connected())
		return;
	if (context() == NULL)
		throw Exception(QObject::tr("Unable to connect."), QObject::tr("Connection has not been properly configured."));
	if (modbus_connect(context()) == 0)
		setConnected(true);
	else
		throw Exception(QObject::tr("Unable to connect."));
}

void AbstractConnection::disconnect()
{
	if (context() != NULL)
		modbus_close(context());
	setConnected(false);
}

int AbstractConnection::readIr(int addr, int num, uint16_t & dest)
{
	return modbus_read_input_registers(context(), addr, num, & dest);
}

int AbstractConnection::readR(int addr, int num, uint16_t & dest)
{
	return modbus_read_registers(context(), addr, num, & dest);
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
