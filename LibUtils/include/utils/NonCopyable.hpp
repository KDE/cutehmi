#ifndef CUTEHMI_LIBUTILS_INCLUDE_UTILS_NONCOPYABLE_HPP
#define CUTEHMI_LIBUTILS_INCLUDE_UTILS_NONCOPYABLE_HPP

namespace cutehmi {
namespace utils {

/**
 * Non-copyable object. This class just locks copy constructor and assignment operator for
 * derived classes.
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
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
