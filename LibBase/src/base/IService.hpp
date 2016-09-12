#ifndef CUTEHMI_LIBBASE_SRC_BASE_ISERVICE_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_ISERVICE_HPP

#include "../platform.hpp"

namespace cutehmi {
namespace base {

class IService
{
	public:
		virtual void init() = 0;

		virtual void start() = 0;

		virtual void stop() = 0;

	protected:
		virtual ~IService() = default;

		IService() = default;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
