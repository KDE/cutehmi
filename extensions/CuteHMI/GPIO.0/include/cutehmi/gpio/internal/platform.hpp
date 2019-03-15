#ifndef H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_INTERNAL_PLATFORM_HPP
#define H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_INTERNAL_PLATFORM_HPP

#include <QtCore/QtGlobal>

#ifdef CUTEHMI_GPIO_DYNAMIC
	#ifdef CUTEHMI_GPIO_BUILD
		//export symbols to dll
		#define CUTEHMI_GPIO_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_GPIO_API Q_DECL_IMPORT
	#endif

	#ifdef CUTEHMI_GPIO_TESTS
		//export symbols to dll
		#define CUTEHMI_GPIO_PRIVATE Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_GPIO_PRIVATE Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_GPIO_API
	#define CUTEHMI_GPIO_PRIVATE
#endif

#endif
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
