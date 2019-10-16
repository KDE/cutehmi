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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
