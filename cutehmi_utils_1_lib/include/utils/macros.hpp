#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_UTILS_MACROS_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_UTILS_MACROS_HPP

#define CUTEHMI_UTILS_FLF " [file: " << __FILE__ << " line: " << __LINE__ << " function: " << __FUNCTION__ << "]"

#ifndef CUTEHMI_NO_UTILS_DEBUG
	#define CUTEHMI_UTILS_DEBUG(CATEGORY, EXPR) cDebug() << "Debug message: " << EXPR << CUTEHMI_UTILS_FLF
#else
	#define CUTEHMI_UTILS_DEBUG(CATEGORY, EXPR) (void)0
#endif

#ifndef CUTEHMI_NO_UTILS_INFO
	#define CUTEHMI_UTILS_INFO(CATEGORY, EXPR) cInfo() << "Note: " << EXPR << CUTEHMI_UTILS_FLF
#else
	#define CUTEHMI_UTILS_INFO(CATEGORY, EXPR) (void)0
#endif

#ifndef CUTEHMI_NO_UTILS_WARNING
	#define CUTEHMI_UTILS_WARNING(CATEGORY, EXPR) cWarning() << "Warning: " << EXPR << CUTEHMI_UTILS_FLF
#else
	#define CUTEHMI_UTILS_WARNING(CATEGORY, EXPR) (void)0
#endif

#ifndef CUTEHMI_NO_UTILS_CRITICAL
	#define CUTEHMI_UTILS_CRITICAL(CATEGORY, EXPR) cCritical() << "Critical error: " << EXPR << CUTEHMI_UTILS_FLF
#else
	#define CUTEHMI_UTILS_CRITICAL(CATEGORY, EXPR) (void)0
#endif

#ifdef CUTEHMI_DEBUG
	#define CUTEHMI_UTILS_ASSERT(EXPR, MSG) Q_ASSERT_X(EXPR, __FILE__, MSG)
#else
	#define CUTEHMI_UTILS_ASSERT(EXPR, MSG) (void)0
#endif

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
