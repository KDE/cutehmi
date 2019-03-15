#ifndef H_EXTENSIONS_CUTEHMI_BITCOINCASH_0_INCLUDE_CUTEHMI_BITCOINCASH_INTERNAL_PLATFORM_HPP
#define H_EXTENSIONS_CUTEHMI_BITCOINCASH_0_INCLUDE_CUTEHMI_BITCOINCASH_INTERNAL_PLATFORM_HPP

#include <QtCore/QtGlobal>

#ifdef CUTEHMI_BITCOINCASH_DYNAMIC
	#ifdef CUTEHMI_BITCOINCASH_BUILD
		//export symbols to dll
		#define CUTEHMI_BITCOINCASH_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_BITCOINCASH_API Q_DECL_IMPORT
	#endif

	#ifdef CUTEHMI_BITCOINCASH_TESTS
		//export symbols to dll
		#define CUTEHMI_BITCOINCASH_PRIVATE Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_BITCOINCASH_PRIVATE Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_BITCOINCASH_API
	#define CUTEHMI_BITCOINCASH_PRIVATE
#endif

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
