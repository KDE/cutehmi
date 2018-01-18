#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_MACROS_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_MACROS_HPP

#include <QLoggingCategory>

#define CUTEHMI_BASE_FLF " [file: " << __FILE__ << " line: " << __LINE__ << " function: " << __FUNCTION__ << "]"

#ifndef CUTEHMI_NO_BASE_QCDEBUG
	#define CUTEHMI_BASE_QCDEBUG(CATEGORY, EXPR) qCDebug(CATEGORY).nospace().noquote() << "Debug message: " << EXPR << CUTEHMI_BASE_FLF
#else
	#define CUTEHMI_BASE_QCDEBUG(CATEGORY, EXPR) (void)0
#endif

#ifndef CUTEHMI_NO_BASE_QCINFO
	#define CUTEHMI_BASE_QCINFO(CATEGORY, EXPR) qCInfo(CATEGORY).nospace().noquote() << "Note: " << EXPR << CUTEHMI_BASE_FLF
#else
	#define CUTEHMI_BASE_QCINFO(CATEGORY, EXPR) (void)0
#endif

#ifndef CUTEHMI_NO_BASE_QCWARNING
	#define CUTEHMI_BASE_QCWARNING(CATEGORY, EXPR) qCWarning(CATEGORY).nospace().noquote() << "Warning: " << EXPR << CUTEHMI_BASE_FLF
#else
	#define CUTEHMI_BASE_QCWARNING(CATEGORY, EXPR) (void)0
#endif

#ifndef CUTEHMI_NO_BASE_QCCRITICAL
	#define CUTEHMI_BASE_QCCRITICAL(CATEGORY, EXPR) qCCritical(CATEGORY).nospace().noquote() << "Critical error: " << EXPR << CUTEHMI_BASE_FLF
#else
	#define CUTEHMI_BASE_QCCRITICAL(CATEGORY, EXPR) (void)0
#endif

#ifdef CUTEHMI_DEBUG
	#define CUTEHMI_UTILS_ASSERT(EXPR, MSG) Q_ASSERT_X(EXPR, __FILE__, MSG)
#else
	#define CUTEHMI_UTILS_ASSERT(EXPR, MSG) (void)0
#endif

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
