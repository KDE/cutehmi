#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_WRAPPERS_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_WRAPPERS_HPP

#include <algorithm>
#include <iterator>

namespace cutehmi {

template <class INPUT_IT, class SIZE, class OUTPUT_IT>
OUTPUT_IT copy_n(INPUT_IT first, SIZE count, OUTPUT_IT result);

template <class INPUT_IT1, class INPUT_IT2>
bool equal(INPUT_IT1 first1, INPUT_IT1 last1, INPUT_IT2 first2);

template <class INPUT_IT, class SIZE, class OUTPUT_IT>
OUTPUT_IT copy_n(INPUT_IT first, SIZE count, OUTPUT_IT result)
{
	// Avoid MSVC C4996 warning, when using std::copy_n with raw pointers.
#ifdef _MSC_VER
	return ::std::copy_n(first, count, ::stdext::checked_array_iterator<OUTPUT_IT>(result, count)).base();
#else
	return ::std::copy_n(first, count, result);
#endif
}

template <class INPUT_IT1, class INPUT_IT2>
bool equal(INPUT_IT1 first1, INPUT_IT1 last1, INPUT_IT2 first2)
{
	// Avoid MSVC C4996 warning, when using std::copy_n with raw pointers.
#ifdef _MSC_VER
	return ::std::equal(first1, last1, ::stdext::make_unchecked_array_iterator(first2));
#else
	return ::std::equal(first1, last1, first2);
#endif
}

}

#endif

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
