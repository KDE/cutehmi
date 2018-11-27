#ifndef H_MODULES_CUTEHMI_u_2_INCLUDE_CUTEHMI_LOGGING_HPP
#define H_MODULES_CUTEHMI_u_2_INCLUDE_CUTEHMI_LOGGING_HPP

#include "loggingMacros.hpp"

Q_DECLARE_LOGGING_CATEGORY(cutehmi_2_loggingCategory)

namespace cutehmi {

inline
const QLoggingCategory & loggingCategory()
{
	return cutehmi_2_loggingCategory();
}

}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
