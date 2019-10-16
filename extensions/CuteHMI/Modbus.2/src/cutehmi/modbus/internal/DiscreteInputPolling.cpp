#include <cutehmi/modbus/internal/DiscreteInputPolling.hpp>

#include <cutehmi/modbus/AbstractDevice.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

DiscreteInputPolling::DiscreteInputPolling(AbstractDevice * device, QUuid * requestId):
	Parent(device, requestId)
{
}

const DiscreteInputPolling::DataContainer & DiscreteInputPolling::container() const
{
	return discreteInputData(device());
}

const DiscreteInputPolling::Data * DiscreteInputPolling::dataAt(quint16 address) const
{
	return discreteInputData(device()).at(address);
}

void DiscreteInputPolling::requestReadData(quint16 address, quint16 amount, QUuid * requestId)
{
	device()->requestReadDiscreteInputs(address, amount, requestId);
}

int DiscreteInputPolling::maxRead() const
{
	return device()->maxReadDiscreteInputs();
}

}
}
}
