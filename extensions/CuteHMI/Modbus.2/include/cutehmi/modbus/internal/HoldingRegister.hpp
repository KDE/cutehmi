#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_HOLDINGREGISTER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_HOLDINGREGISTER_HPP

#include "../HoldingRegister.hpp"

#include <QAtomicInteger>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Internal holding register. This is internal class that exposes protected functions such as setValue().
 */
class CUTEHMI_MODBUS_API HoldingRegister:
	public ::cutehmi::modbus::HoldingRegister
{
		typedef ::cutehmi::modbus::HoldingRegister Parent;

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 */
		explicit HoldingRegister(quint16 value = 0);

		using Parent::setValue;
};

}
}
}

#endif

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
