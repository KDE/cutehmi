#include "PLCClientManager.hpp"
#include "../modbus/TCPConnection.hpp"

namespace base {

PLCClientManager::PLCClientManager():
	m_modbusClient(std::unique_ptr<modbus::TCPConnection>(new modbus::TCPConnection("127.0.0.1", "1502")))
{
}

}
