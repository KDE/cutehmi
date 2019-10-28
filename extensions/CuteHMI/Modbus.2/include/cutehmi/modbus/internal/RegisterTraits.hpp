#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_REGISTERTRAITS_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_REGISTERTRAITS_HPP

#include "DataContainer.hpp"
#include "InputRegister.hpp"
#include "HoldingRegister.hpp"
#include "DiscreteInput.hpp"
#include "Coil.hpp"

namespace cutehmi {
namespace modbus {
namespace internal {

template <typename R>
struct RegisterTraits
{
};

template <>
struct RegisterTraits<InputRegister>
{
	typedef DataContainer<InputRegister> Container;
};

template <>
struct RegisterTraits<HoldingRegister>
{
	typedef DataContainer<HoldingRegister> Container;
};

template <>
struct RegisterTraits<DiscreteInput>
{
	typedef DataContainer<DiscreteInput> Container;
};

template <>
struct RegisterTraits<Coil>
{
	typedef DataContainer<Coil> Container;
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
