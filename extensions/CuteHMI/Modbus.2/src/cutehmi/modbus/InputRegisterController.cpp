#include <cutehmi/modbus/InputRegisterController.hpp>

namespace cutehmi {
namespace modbus {

InputRegisterController::InputRegisterController(QObject * parent):
	Register16Controller(parent)
{
}

Register16 * InputRegisterController::registerAt(quint16 address) const
{
	return device()->inputRegisterAt(address);
}

void InputRegisterController::requestReadRegisters(quint16 address, quint16 amount, QUuid * requestId) const
{
	device()->requestReadInputRegisters(address, amount, requestId);
}

void InputRegisterController::requestWriteRegister(quint16 address, quint16 value, QUuid * requestId) const
{
	device()->requestWriteInputRegister(address, value, requestId);
}

AbstractDevice::Function InputRegisterController::readRegistersFunction() const
{
	return AbstractDevice::FUNCTION_READ_INPUT_REGISTERS;
}

AbstractDevice::Function InputRegisterController::writeRegisterFunction() const
{
	return AbstractDevice::FUNCTION_WRITE_INPUT_REGISTER;
}

}
}
