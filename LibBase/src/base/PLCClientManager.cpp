#include "PLCClientManager.hpp"
#include "../modbus/TCPConnection.hpp"

namespace base {

PLCClientManager::PLCClientManager()
{
	std::unique_ptr<modbus::TCPConnection> connection(new modbus::TCPConnection("127.0.0.1", "1502"));
	connection->setByteTimeout(modbus::AbstractConnection::Timeout{5, 0});
	connection->setResponseTimeout(modbus::AbstractConnection::Timeout{5, 0});
	m_modbusClient = new modbus::Client(std::move(connection));
}

}
