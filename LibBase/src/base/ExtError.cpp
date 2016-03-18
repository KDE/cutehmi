#include "ExtError.hpp"

namespace cutehmi {
namespace base {

ExtError::ExtError(int code, const QString & details):
	Error(code),
	m_details(details)
{
}

QString ExtError::details() const
{
	return m_details;
}

void ExtError::setDetails(const QString & details)
{
	m_details = details;
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
