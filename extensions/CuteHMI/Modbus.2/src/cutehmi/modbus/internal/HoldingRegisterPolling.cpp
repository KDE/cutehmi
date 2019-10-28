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

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
