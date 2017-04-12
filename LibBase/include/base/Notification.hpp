#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_NOTIFICATION_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_NOTIFICATION_HPP

#include "internal/common.hpp"
#include "ErrorInfo.hpp"

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API Notification
{
	public:
		static void Note(const QString & text);

		static void Warning(const QString & text);

		static void Critical(const QString & text);

		static void Critical(const ErrorInfo & errorInfo);

};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
