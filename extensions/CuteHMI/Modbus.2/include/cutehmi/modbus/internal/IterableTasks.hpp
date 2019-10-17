#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ITERABLETASKS_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ITERABLETASKS_HPP

#include "common.hpp"
#include "RegisterTraits.hpp"

#include <cutehmi/NonCopyable.hpp>

namespace cutehmi {
namespace modbus {

class AbstractDevice;

namespace internal {

class CUTEHMI_MODBUS_PRIVATE IterableTasks:
	public cutehmi::NonCopyable
{
	public:
		typedef typename RegisterTraits<Coil>::Container CoilDataContainer;
		typedef typename RegisterTraits<DiscreteInput>::Container DiscreteInputDataContainer;
		typedef typename RegisterTraits<HoldingRegister>::Container HoldingRegisterDataContainer;
		typedef typename RegisterTraits<InputRegister>::Container InputRegisterDataContainer;

		virtual ~IterableTasks() = default;

		/**
		 * Run next task.
		 * @return @p false if there are no more tasks to run, @p true otherwise.
		 */
		virtual bool runNext() = 0;

		/**
		 * Reset tasks iterator.
		 */
		virtual void reset() = 0;

		const CoilDataContainer & coilData(const AbstractDevice * device) const;

		const DiscreteInputDataContainer & discreteInputData(const AbstractDevice * device) const;

		const HoldingRegisterDataContainer & holdingRegisterData(const AbstractDevice * device) const;

		const InputRegisterDataContainer & inputRegisterData(const AbstractDevice * device) const;
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
