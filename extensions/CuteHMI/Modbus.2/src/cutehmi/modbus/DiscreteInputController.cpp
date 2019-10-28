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

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
