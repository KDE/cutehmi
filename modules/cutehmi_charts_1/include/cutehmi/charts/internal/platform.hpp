#ifndef H_MODULES_CUTEHMI__CHARTS__1_INCLUDE_CUTEHMI_CHARTS_INTERNAL_PLATFORM_HPP
#define H_MODULES_CUTEHMI__CHARTS__1_INCLUDE_CUTEHMI_CHARTS_INTERNAL_PLATFORM_HPP

#include <QtGlobal>

#ifdef CUTEHMI_CHARTS_DYNAMIC
	#ifdef CUTEHMI_CHARTS_BUILD
		//export symbols to dll
		#define CUTEHMI_CHARTS_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_CHARTS_API Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_CHARTS_API
#endif

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
