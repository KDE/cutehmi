#ifndef H_MODULES_CUTEHMI_u_STUPID_u_1_INCLUDE_CUTEHMI_STUPID_INTERNAL_PLATFORM_HPP
#define H_MODULES_CUTEHMI_u_STUPID_u_1_INCLUDE_CUTEHMI_STUPID_INTERNAL_PLATFORM_HPP

#include <QtGlobal>

#ifdef CUTEHMI_STUPID_DYNAMIC
	#ifdef CUTEHMI_STUPID_BUILD
		//export symbols to dll
		#define CUTEHMI_STUPID_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_STUPID_API Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_STUPID_API
#endif

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
