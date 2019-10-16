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
