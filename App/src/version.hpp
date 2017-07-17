#ifndef CUTEHMI_APP_SRC_VERSION_HPP
#define CUTEHMI_APP_SRC_VERSION_HPP

//1 for development version, 0 for release
#define CUTEHMI_VERSION_IS_DEV 1
#define CUTEHMI_VERSION_BRANCH "master"
#define CUTEHMI_APP_COPYRIGHT_YEAR "2015-2017"

#ifndef NDEBUG
	#define CUTEHMI_VERSION_DEBUG_QUALIFIER ".debug"
#else
	#define CUTEHMI_VERSION_DEBUG_QUALIFIER ""
#endif

#if CUTEHMI_VERSION_IS_DEV == 1
	#define CUTEHMI_VERSION_DEV_QUALIFIER ".dev"
#else
	#define CUTEHMI_VERSION_DEV_QUALIFIER ""
#endif

#define CUTEHMI_APP_VERSION CUTEHMI_VERSION_BRANCH CUTEHMI_VERSION_DEBUG_QUALIFIER CUTEHMI_VERSION_DEV_QUALIFIER

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
