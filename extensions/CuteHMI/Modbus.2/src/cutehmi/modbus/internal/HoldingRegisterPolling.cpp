#include <cutehmi/modbus/internal/HoldingRegisterPolling.hpp>

#include <cutehmi/modbus/AbstractDevice.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

HoldingRegisterPolling::HoldingRegisterPolling(AbstractDevice * device, QUuid * requestId):
	Parent(device, requestId)
{
}

const HoldingRegisterPolling::DataContainer & HoldingRegisterPolling::container() const
{
	return holdingRegisterData(device());
}

const HoldingRegisterPolling::Data * HoldingRegisterPolling::dataAt(quint16 address) const
{
	return holdingRegisterData(device()).at(address);
}

void HoldingRegisterPolling::requestReadData(quint16 address, quint16 amount, QUuid * requestId)
{
	device()->requestReadHoldingRegisters(address, amount, requestId);
}

int HoldingRegisterPolling::maxRead() const
{
	return device()->maxReadHoldingRegisters();
}

}
}
}
