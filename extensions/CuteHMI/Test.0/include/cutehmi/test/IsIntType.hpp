#ifndef H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_ISINTTYPE_HPP
#define H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_ISINTTYPE_HPP

#include "IsAnyOfTypes.hpp"

namespace cutehmi {
namespace test {

/**
 * Check if template parameter is of integer type.
 * @tparam T parameter to check.
 * @return if @a T is an integer, structure provides a member constant @a value
 * equal to @p true. Otherwise @a value is @p false.
 */
template<typename T>
struct IsIntType:
	IsAnyOfTypes<T, short, int, long, long long, unsigned short, unsigned int, unsigned long, unsigned long long>
{
};

}
}

#endif

//(c)MP: Copyright © 2018-2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
