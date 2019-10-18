#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_PLATFORM_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_PLATFORM_HPP

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

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
