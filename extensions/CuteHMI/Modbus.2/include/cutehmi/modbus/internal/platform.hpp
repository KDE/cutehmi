#ifndef H_MODULES_CUTEHMI_u_MODBUS_u_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_PLATFORM_HPP
#define H_MODULES_CUTEHMI_u_MODBUS_u_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_PLATFORM_HPP

#include <QtGlobal>

#ifdef CUTEHMI_MODBUS_DYNAMIC
	#ifdef CUTEHMI_MODBUS_BUILD
		//export symbols to dll
		#define CUTEHMI_MODBUS_API Q_DECL_EXPORT
		#ifdef CUTEHMI_MODBUS_TESTS
			//export symbols to dll
			#define CUTEHMI_MODBUS_PRIVATE Q_DECL_EXPORT
		#else
			#define CUTEHMI_MODBUS_PRIVATE
		#endif
	#else
		//using functions from dll
		#define CUTEHMI_MODBUS_API Q_DECL_IMPORT
		#ifdef CUTEHMI_MODBUS_TESTS
			//using functions from dll
			#define CUTEHMI_MODBUS_PRIVATE Q_DECL_IMPORT
		#else
			#define CUTEHMI_MODBUS_PRIVATE
		#endif
	#endif
#else
	#define CUTEHMI_MODBUS_API
	#define CUTEHMI_MODBUS_PRIVATE
#endif

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
