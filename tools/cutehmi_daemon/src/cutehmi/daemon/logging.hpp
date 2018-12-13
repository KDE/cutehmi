#ifndef H_TOOLS_CUTEHMI_u_DAEMON_u_1_INCLUDE_CUTEHMI_DAEMON_LOGGING_HPP
#define H_TOOLS_CUTEHMI_u_DAEMON_u_1_INCLUDE_CUTEHMI_DAEMON_LOGGING_HPP

#include <cutehmi/loggingMacros.hpp>

Q_DECLARE_LOGGING_CATEGORY(cutehmi_daemon_loggingCategory)

namespace cutehmi {
namespace daemon {

inline
const QLoggingCategory & loggingCategory()
{
	return cutehmi_daemon_loggingCategory();
}

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
