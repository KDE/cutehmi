#ifndef H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_NONCOPYABLE_HPP
#define H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_NONCOPYABLE_HPP

namespace cutehmi {

/**
 * Non-copyable object. This class just locks copy constructor and assignment
 * operator for derived classes.
 */
class NonCopyable
{
	protected:
		NonCopyable() = default;

		NonCopyable(NonCopyable && other) = default;

		~NonCopyable() = default;

		NonCopyable & operator =(NonCopyable && other) = default;

	private:
		NonCopyable(const NonCopyable & other) = delete;

		NonCopyable & operator =(const NonCopyable & other) = delete;
};

}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
