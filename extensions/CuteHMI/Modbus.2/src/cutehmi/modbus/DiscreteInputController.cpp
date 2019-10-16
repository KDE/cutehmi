#include <cutehmi/modbus/DiscreteInputController.hpp>

namespace cutehmi {
namespace modbus {

DiscreteInputController::DiscreteInputController(QObject * parent):
	Register1Controller(parent)
{
}

Register1 * DiscreteInputController::registerAt(quint16 address) const
{
	return device()->discreteInputAt(address);
}

void DiscreteInputController::requestReadRegisters(quint16 address, quint16 amount, QUuid * requestId) const
{
	device()->requestReadDiscreteInputs(address, amount, requestId);
}

void DiscreteInputController::requestWriteRegister(quint16 address, bool value, QUuid * requestId) const
{
	device()->requestWriteDiscreteInput(address, value, requestId);
}

AbstractDevice::Function DiscreteInputController::readRegistersFunction() const
{
	return AbstractDevice::FUNCTION_READ_DISCRETE_INPUTS;
}

AbstractDevice::Function DiscreteInputController::writeRegisterFunction() const
{
	return AbstractDevice::FUNCTION_WRITE_DISCRETE_INPUT;
}


}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
