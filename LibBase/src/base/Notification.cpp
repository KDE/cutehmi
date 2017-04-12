#include "../../include/base/Notification.hpp"

namespace cutehmi {
namespace base {

void Notification::Note(const QString & text)
{
	CUTEHMI_BASE_QINFO(text);		//temp
}

void Notification::Warning(const QString & text)
{
	CUTEHMI_BASE_QWARNING(text);	//temp
}

void Notification::Critical(const QString & text)
{
	CUTEHMI_BASE_QCRITICAL(text);	//temp
}

void Notification::Critical(const ErrorInfo & errorInfo)
{
	return Critical(errorInfo.toString());
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
