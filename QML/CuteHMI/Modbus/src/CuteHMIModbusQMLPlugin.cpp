#include "CuteHMIModbusQMLPlugin.hpp"

#include <modbus/HoldingRegister.hpp>
#include <modbus/InputRegister.hpp>
#include <modbus/DiscreteInput.hpp>
#include <modbus/Coil.hpp>

#include <QtQml>

void CuteHMIModbusQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Modbus"));
	qmlRegisterType<cutehmi::modbus::InputRegister>(uri, 1, 0, "ModbusInputRegister");
	qmlRegisterType<cutehmi::modbus::HoldingRegister>(uri, 1, 0, "ModbusHoldingRegister");
	qmlRegisterType<cutehmi::modbus::DiscreteInput>(uri, 1, 0, "ModbusDiscreteInput");
	qmlRegisterType<cutehmi::modbus::Coil>(uri, 1, 0, "ModbusCoil");
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
