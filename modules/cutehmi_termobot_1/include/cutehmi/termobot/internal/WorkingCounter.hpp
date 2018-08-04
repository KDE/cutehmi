#ifndef H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_INTERNAL_WORKINGCOUNTER_HPP
#define H_MODULES_CUTEHMI__TERMOBOT__1_INCLUDE_CUTEHMI_TERMOBOT_INTERNAL_WORKINGCOUNTER_HPP

#include <functional>

namespace cutehmi {
namespace termobot {
namespace internal {

class WorkingCounter
{
	public:
		WorkingCounter(std::function<void()> busyChanged);

		WorkingCounter & operator ++();

		WorkingCounter & operator --();

		operator bool() const;

		int m_counter;
	private:
		std::function<void()> m_busyChanged;
};

}
}
}

#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
