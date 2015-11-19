#include "ClientPlugin.hpp"
#include "InputRegister.hpp"
#include "HoldingRegister.hpp"

#include <QtQml>

#include <memory>

namespace modbus {

ClientPlugin::ClientPlugin()
{
	qmlRegisterType<InputRegister>("pl.ekterm.libcutehmibase.modbus", 1, 0, "ModbusInputRegister");
	qmlRegisterType<HoldingRegister>("pl.ekterm.libcutehmibase.modbus", 1, 0, "ModbusHoldingRegister");
}

Client * ClientPlugin::createClient() const
{
//	std::unique_ptr<TCPConnection> tcpConnection(new TCPConnection("127.0.0.1", "502"));

//	m_tcpModbusConnection("127.0.0.1", "1502");

}

QWidget * ClientPlugin::createControlWidget() const
{

}

}
