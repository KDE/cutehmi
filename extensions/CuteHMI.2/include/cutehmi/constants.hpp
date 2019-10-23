#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_CONSTANTS_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_CONSTANTS_HPP

#include <QtGlobal>

namespace cutehmi {

/**
 * CuteHMI epsilon. This constant is used in fuzzy comparison functions.
 *
 * @internal Machine epsilon * 0.5 is smallest possible epsilon for which approximation functions make sense.
 */
constexpr qreal EPS = std::numeric_limits<qreal>::epsilon() * 0.5 * 0x10000;	// eps * 0.5 * 2^16.

}

#endif

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
