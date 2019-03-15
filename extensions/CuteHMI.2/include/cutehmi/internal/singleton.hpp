#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INTERNAL_SINGLETON_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INTERNAL_SINGLETON_HPP

#include "platform.hpp"


namespace cutehmi {
namespace internal {

typedef void(*singletonDestroyCallback)();

CUTEHMI_PRIVATE void destroySingletonInstances();

CUTEHMI_PRIVATE void storeSingletonDestroyCallback(singletonDestroyCallback callback);

CUTEHMI_PRIVATE void removeSingletonDestroyCallback(singletonDestroyCallback callback);

}
}

#endif
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
