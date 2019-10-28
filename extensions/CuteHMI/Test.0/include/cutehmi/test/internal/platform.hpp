#ifndef H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_INTERNAL_PLATFORM_HPP
#define H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_INTERNAL_PLATFORM_HPP

#include <QtCore/QtGlobal>

#ifdef CUTEHMI_TEST_DYNAMIC
	#ifdef CUTEHMI_TEST_BUILD
		// Export symbols to dynamic library.
		#define CUTEHMI_TEST_API Q_DECL_EXPORT
		#ifdef CUTEHMI_TEST_TESTS
			// Export symbols to dynamic library.
			#define CUTEHMI_TEST_PRIVATE Q_DECL_EXPORT
		#else
			#define CUTEHMI_TEST_PRIVATE
		#endif
	#else
		// Using symbols from dynamic library.
		#define CUTEHMI_TEST_API Q_DECL_IMPORT
		#ifdef CUTEHMI_TEST_TESTS
			// Using symbols from dynamic library.
			#define CUTEHMI_TEST_PRIVATE Q_DECL_IMPORT
		#else
			#define CUTEHMI_TEST_PRIVATE
		#endif
	#endif
#else
	#define CUTEHMI_TEST_API
	#define CUTEHMI_TEST_PRIVATE
#endif

#endif

//(c)C: Copyright © 2018-2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
