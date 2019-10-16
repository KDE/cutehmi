#include <cutehmi/modbus/internal/CoilPolling.hpp>

#include <cutehmi/modbus/AbstractDevice.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

CoilPolling::CoilPolling(AbstractDevice * device, QUuid * requestId):
	Parent(device, requestId)
{
}

const CoilPolling::DataContainer & CoilPolling::container() const
{
	return coilData(device());
}

const CoilPolling::Data * CoilPolling::dataAt(quint16 address) const
{
	return coilData(device()).at(address);
}

void CoilPolling::requestReadData(quint16 address, quint16 amount, QUuid * requestId)
{
	device()->requestReadCoils(address, amount, requestId);
}

int CoilPolling::maxRead() const
{
	return device()->maxReadCoils();
}

}
}
}
