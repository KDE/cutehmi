#ifndef H_MODULES_CUTEHMI_u_APP_u_1_INCLUDE_CUTEHMI_APP_LOGGING_HPP
#define H_MODULES_CUTEHMI_u_APP_u_1_INCLUDE_CUTEHMI_APP_LOGGING_HPP

#include "internal/platform.hpp"
#include <cutehmi/loggingMacros.hpp>

CUTEHMI_APP_API Q_DECLARE_LOGGING_CATEGORY(cutehmi_app_2_loggingCategory)

namespace cutehmi {
namespace app {

inline
const QLoggingCategory & loggingCategory()
{
	return cutehmi_app_2_loggingCategory();
}

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
