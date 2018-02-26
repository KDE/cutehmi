#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_XML_INTERNAL_PLATFORM_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_XML_INTERNAL_PLATFORM_HPP

#ifdef CUTEHMI_XML_DYNAMIC
	#ifdef CUTEHMI_XML_BUILD
		//export symbols to dll
		#define CUTEHMI_XML_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_XML_API Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_XML_API
#endif

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
