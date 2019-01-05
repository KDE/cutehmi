#include "../../include/cutehmi/Singleton.hpp"
#include "../../include/cutehmi/CuteHMI.hpp"

namespace cutehmi {

void destroySingletonInstances()
{
	internal::destroySingletonInstances();
	CuteHMI::Destroy();		// Until CuteHMI is not removed (or extends Singleton).
}

}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
