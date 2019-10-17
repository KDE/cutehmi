#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DISCRETEINPUTPOLLING_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DISCRETEINPUTPOLLING_HPP

#include "common.hpp"
#include "DataContainerPolling.hpp"

class QUuid;

namespace cutehmi {
namespace modbus {
namespace internal {

class CUTEHMI_MODBUS_PRIVATE DiscreteInputPolling:
	public DataContainerPolling<DiscreteInputPolling, DiscreteInput>
{
		typedef DataContainerPolling<DiscreteInputPolling, DiscreteInput> Parent;

	public:
		DiscreteInputPolling(AbstractDevice * device, QUuid * requestId);

		const DataContainer & container() const;

		const Data * dataAt(quint16 address) const;

		void requestReadData(quint16 address, quint16 amount, QUuid * requestId);

		int maxRead() const;
};

}
}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
