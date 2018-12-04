#ifndef H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_NONMOVABLE_HPP
#define H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_NONMOVABLE_HPP

namespace cutehmi {

/**
 * Non-movable object. This class just locks move constructor and move assignment operator for
 * derived classes.
 */
class NonMovable
{
	protected:
		NonMovable() = default;

	private:
		NonMovable(NonMovable && other) = delete;

		NonMovable & operator =(NonMovable && other) = delete;
};

}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
