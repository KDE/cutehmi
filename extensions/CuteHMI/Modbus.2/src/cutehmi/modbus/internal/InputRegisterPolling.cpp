#include <cutehmi/modbus/internal/InputRegisterPolling.hpp>

#include <cutehmi/modbus/AbstractDevice.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

InputRegisterPolling::InputRegisterPolling(AbstractDevice * device, QUuid * requestId):
	Parent(device, requestId)
{
}

const InputRegisterPolling::DataContainer & InputRegisterPolling::container() const
{
	return inputRegisterData(device());
}

const InputRegisterPolling::Data * InputRegisterPolling::dataAt(quint16 address) const
{
	return inputRegisterData(device()).at(address);
}

void InputRegisterPolling::requestReadData(quint16 address, quint16 amount, QUuid * requestId)
{
	device()->requestReadInputRegisters(address, amount, requestId);
}

int InputRegisterPolling::maxRead() const
{
	return device()->maxReadInputRegisters();
}

}
}
}
