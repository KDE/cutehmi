#include <cutehmi/modbus/CoilController.hpp>

namespace cutehmi {
namespace modbus {

CoilController::CoilController(QObject * parent):
	Register1Controller(parent)
{
}

Register1 * CoilController::registerAt(quint16 address) const
{
	return device()->coilAt(address);
}

void CoilController::requestReadRegisters(quint16 address, quint16 amount, QUuid * requestId) const
{
	device()->requestReadCoils(address, amount, requestId);
}

void CoilController::requestWriteRegister(quint16 address, bool value, QUuid * requestId) const
{
	device()->requestWriteCoil(address, value, requestId);
}

AbstractDevice::Function CoilController::readRegistersFunction() const
{
	return AbstractDevice::FUNCTION_READ_COILS;
}

AbstractDevice::Function CoilController::writeRegisterFunction() const
{
	return AbstractDevice::FUNCTION_WRITE_COIL;
}


}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
