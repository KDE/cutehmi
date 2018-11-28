#ifndef H_MODULES_CUTEHMI_u_TEST_u_1_INCLUDE_CUTEHMI_TEST_ISANYOFTYPES_HPP
#define H_MODULES_CUTEHMI_u_TEST_u_1_INCLUDE_CUTEHMI_TEST_ISANYOFTYPES_HPP

#include <type_traits>

namespace cutehmi {
namespace test {

/**
 * Check if template parameter is one of the types specified by @a TYPES.
 * @tparam T paremeter to check.
 * @tparam TYPES types to check.
 * @return if @a T is of one of the types specified by @a TYPES, structure provides
 * a member constant @a value equal to @p true. Otherwise @a value is @p false.
 *
 * @note implementation comes from https://stackoverflow.com/a/17032517/205955.
 */
template<typename T, typename... TYPES>
struct IsAnyOfTypes:
	std::false_type
{
};

template<typename T, typename TYPE>
struct IsAnyOfTypes<T, TYPE>:
	std::is_same<T, TYPE>
{
};

template<typename T, typename TYPE, typename... TYPES>
struct IsAnyOfTypes<T, TYPE, TYPES...>:
	std::integral_constant<bool, std::is_same<T, TYPE>::value || IsAnyOfTypes<T, TYPES...>::value>
{
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
