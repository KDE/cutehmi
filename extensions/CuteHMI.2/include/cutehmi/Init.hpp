#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INIT_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INIT_HPP

#include "Initializer.hpp"

namespace cutehmi {

/**
 * %Init. This class performs initialization of CuteHMI extension.
 *
 * Normally it is not advisable to create custom instances of this class as extension provides an instance on its own. This can be
 * invalidated particulary by static builds in which case a global variable may not get into resulting binary.
 *
 * Classes registered as meta types:
 *	- ErrorInfo
 *	- InplaceError
 *	- Message::Button
 *  .
 *
 * Classes registered as meta types can be used in string-based, queued signal-slot connections and various functions that rely on
 * QMetaType features.
 */
class CUTEHMI_API Init final:
	public Initializer<Init>
{
	public:
		/**
		 * Default constructor.
		 */
		Init();
};

}

#endif

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
