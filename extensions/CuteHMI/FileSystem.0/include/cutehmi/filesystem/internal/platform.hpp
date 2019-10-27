#ifndef H_EXTENSIONS_CUTEHMI_FILESYSTEM_0_INCLUDE_CUTEHMI_FILESYSTEM_INTERNAL_PLATFORM_HPP
#define H_EXTENSIONS_CUTEHMI_FILESYSTEM_0_INCLUDE_CUTEHMI_FILESYSTEM_INTERNAL_PLATFORM_HPP

#include <QtCore/QtGlobal>

#ifdef CUTEHMI_FILESYSTEM_DYNAMIC
	#ifdef CUTEHMI_FILESYSTEM_BUILD
		// Export symbols to dynamic library.
		#define CUTEHMI_FILESYSTEM_API Q_DECL_EXPORT
		#ifdef CUTEHMI_FILESYSTEM_TESTS
			// Export symbols to dynamic library.
			#define CUTEHMI_FILESYSTEM_PRIVATE Q_DECL_EXPORT
		#else
			#define CUTEHMI_FILESYSTEM_PRIVATE
		#endif
	#else
		// Using symbols from dynamic library.
		#define CUTEHMI_FILESYSTEM_API Q_DECL_IMPORT
		#ifdef CUTEHMI_FILESYSTEM_TESTS
			// Using symbols from dynamic library.
			#define CUTEHMI_FILESYSTEM_PRIVATE Q_DECL_IMPORT
		#else
			#define CUTEHMI_FILESYSTEM_PRIVATE
		#endif
	#endif
#else
	#define CUTEHMI_FILESYSTEM_API
	#define CUTEHMI_FILESYSTEM_PRIVATE
#endif

#endif

//(c)C: Copyright © 2019, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
