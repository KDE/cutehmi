#ifndef CUTEHMI_LIBWIDGETS_SRC_PLATFORM_HPP
#define CUTEHMI_LIBWIDGETS_SRC_PLATFORM_HPP

#include <QtGlobal>

#ifdef CUTEHMI_WIDGETS_DYNAMIC
	#ifdef CUTEHMI_WIDGETS_BUILD
		//export symbols to dll
		#define CUTEHMI_WIDGETS_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_WIDGETS_API Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_WIDGETS_API
#endif

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
