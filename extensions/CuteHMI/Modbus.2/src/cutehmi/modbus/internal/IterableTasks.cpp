#include <cutehmi/modbus/internal/IterableTasks.hpp>

#include <cutehmi/modbus/AbstractDevice.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

const IterableTasks::DiscreteInputDataContainer & IterableTasks::discreteInputData(const AbstractDevice * device) const
{
	return device->discreteInputData();
}

const IterableTasks::CoilDataContainer & IterableTasks::coilData(const AbstractDevice * device) const
{
	return device->coilData();
}

const IterableTasks::HoldingRegisterDataContainer & IterableTasks::holdingRegisterData(const AbstractDevice * device) const
{
	return device->holdingRegisterData();
}

const IterableTasks::InputRegisterDataContainer & IterableTasks::inputRegisterData(const AbstractDevice * device) const
{
	return device->inputRegisterData();
}

}
}
}
