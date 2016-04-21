#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_REGISTERTRAITS_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_REGISTERTRAITS_HPP

#include "InputRegister.hpp"
#include "HoldingRegister.hpp"
#include "DiscreteInput.hpp"
#include "Coil.hpp"

namespace cutehmi {
namespace modbus {

template <typename R>
struct RegisterTraits
{
	typedef typename RegisterTraits<R>::Container Container;
};

template <>
struct RegisterTraits<InputRegister>
{
	typedef QHash<int, InputRegister *> Container;
};

template <>
struct RegisterTraits<HoldingRegister>
{
	typedef QHash<int, HoldingRegister *> Container;
};

template <>
struct RegisterTraits<DiscreteInput>
{
	typedef QHash<int, DiscreteInput *> Container;
};

template <>
struct RegisterTraits<Coil>
{
	typedef QHash<int, Coil *> Container;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
