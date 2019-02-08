#ifndef H_MODULES_CUTEHMI_u_APP_u_1_INCLUDE_CUTEHMI_APP_INTERNAL_PLATFORM_HPP
#define H_MODULES_CUTEHMI_u_APP_u_1_INCLUDE_CUTEHMI_APP_INTERNAL_PLATFORM_HPP

#ifdef CUTEHMI_APP_DYNAMIC
	#ifdef CUTEHMI_APP_BUILD
		//export symbols to dll
		#define CUTEHMI_APP_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_APP_API Q_DECL_IMPORT
	#endif

	#ifdef CUTEHMI_APP_TESTS
		//export symbols to dll
		#define CUTEHMI_APP_PRIVATE Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_APP_PRIVATE Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_APP_API
	#define CUTEHMI_APP_PRIVATE
#endif

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
