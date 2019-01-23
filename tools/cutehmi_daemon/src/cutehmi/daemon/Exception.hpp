#ifndef H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_EXCEPTION_HPP
#define H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_EXCEPTION_HPP

#include <cutehmi/ExceptionMixin.hpp>

namespace cutehmi {
namespace daemon {

class Exception:
	public ExceptionMixin<Exception>
{
	typedef ExceptionMixin<Exception> Parent;

	public:
		Exception(const QString & what);
};

}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
