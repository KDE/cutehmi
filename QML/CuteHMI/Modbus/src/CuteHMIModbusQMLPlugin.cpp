#include "CuteHMIModbusQMLPlugin.hpp"

#include <modbus/HoldingRegister.hpp>
#include <modbus/InputRegister.hpp>

#include <QtQml>

void CuteHMIModbusQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Modbus"));
	qmlRegisterType<modbus::InputRegister>(uri, 1, 0, "ModbusInputRegister");
	qmlRegisterType<modbus::HoldingRegister>(uri, 1, 0, "ModbusHoldingRegister");
}
