#ifndef H_MODULES_CUTEHMI_u_AUTHSSH_u_1_INCLUDE_CUTEHMI_AUTHSSH_EXCEPTION_HPP
#define H_MODULES_CUTEHMI_u_AUTHSSH_u_1_INCLUDE_CUTEHMI_AUTHSSH_EXCEPTION_HPP

#include "internal/common.hpp"

#include <cutehmi/ExceptionMixin.hpp>

namespace cutehmi {
namespace authssh {

class CUTEHMI_AUTHSSH_API Exception:
	public ExceptionMixin<Exception>
{
	typedef ExceptionMixin<Exception> Parent;

	public:
		using Parent::Parent;

		~Exception() override = default;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
