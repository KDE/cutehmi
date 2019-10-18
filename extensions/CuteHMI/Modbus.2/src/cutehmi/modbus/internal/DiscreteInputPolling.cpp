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

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
