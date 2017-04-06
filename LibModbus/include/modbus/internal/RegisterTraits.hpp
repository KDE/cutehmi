#ifndef CUTEHMI_LIBMODBUS_INCLUDE_MODBUS_INTERNAL_REGISTERTRAITS_HPP
#define CUTEHMI_LIBMODBUS_INCLUDE_MODBUS_INTERNAL_REGISTERTRAITS_HPP

#include "DataContainer.hpp"
#include "../InputRegister.hpp"
#include "../HoldingRegister.hpp"
#include "../DiscreteInput.hpp"
#include "../Coil.hpp"

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
	typedef DataContainer<InputRegister *> Container;
};

template <>
struct RegisterTraits<HoldingRegister>
{
	typedef DataContainer<HoldingRegister *> Container;
};

template <>
struct RegisterTraits<DiscreteInput>
{
	typedef DataContainer<DiscreteInput *> Container;
};

template <>
struct RegisterTraits<Coil>
{
	typedef DataContainer<Coil *> Container;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
