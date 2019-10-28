#include <cutehmi/modbus/HoldingRegisterController.hpp>

namespace cutehmi {
namespace modbus {

HoldingRegisterController::HoldingRegisterController(QObject * parent):
	Register16Controller(parent)
{
}

Register16 * HoldingRegisterController::registerAt(quint16 address) const
{
	return device()->holdingRegisterAt(address);
}

void HoldingRegisterController::requestReadRegisters(quint16 address, quint16 amount, QUuid * requestId) const
{
	device()->requestReadHoldingRegisters(address, amount, requestId);
}

void HoldingRegisterController::requestWriteRegister(quint16 address, quint16 value, QUuid * requestId) const
{
	device()->requestWriteHoldingRegister(address, value, requestId);
}

AbstractDevice::Function HoldingRegisterController::readRegistersFunction() const
{
	return AbstractDevice::FUNCTION_READ_HOLDING_REGISTERS;
}

AbstractDevice::Function HoldingRegisterController::writeRegisterFunction() const
{
	return AbstractDevice::FUNCTION_WRITE_HOLDING_REGISTER;
}

}
}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
