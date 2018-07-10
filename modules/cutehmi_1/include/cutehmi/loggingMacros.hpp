#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_LOGGINGMACROS_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_LOGGINGMACROS_HPP

#include <QLoggingCategory>

#define CUTEHMI_LOG_FLF " [file: " << __FILE__ << " line: " << __LINE__ << " function: " << __FUNCTION__ << "]"

#ifndef CUTEHMI_NO_LOG_DEBUG
	#define CUTEHMI_LOG_DEBUG(EXPR) qCDebug(loggingCategory()).nospace().noquote() << "[debug] " << EXPR << CUTEHMI_LOG_FLF
#else
	#define CUTEHMI_LOG_DEBUG(EXPR) (void)0
#endif

#ifndef CUTEHMI_NO_LOG_INFO
	#define CUTEHMI_LOG_INFO(EXPR) qCInfo(loggingCategory()).nospace().noquote() << "[note] " << EXPR << CUTEHMI_LOG_FLF
#else
	#define CUTEHMI_LOG_INFO(EXPR) (void)0
#endif

#ifndef CUTEHMI_NO_LOG_WARNING
	#define CUTEHMI_LOG_WARNING(EXPR) qCWarning(loggingCategory()).nospace().noquote() << "[warning] " << EXPR << CUTEHMI_LOG_FLF
#else
	#define CUTEHMI_LOG_WARNING(EXPR) (void)0
#endif

#ifndef CUTEHMI_NO_LOG_CRITICAL
	#define CUTEHMI_LOG_CRITICAL(EXPR) qCCritical(loggingCategory()).nospace().noquote() << "[critical] " << EXPR << CUTEHMI_LOG_FLF
#else
	#define CUTEHMI_LOG_CRITICAL(EXPR) (void)0
#endif

#ifdef CUTEHMI_DEBUG
	#define CUTEHMI_ASSERT(EXPR, MSG) Q_ASSERT_X(EXPR, __FILE__, MSG)
#else
	#define CUTEHMI_ASSERT(EXPR, MSG) (void)0
#endif

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
