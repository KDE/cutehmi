#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_LOGGINGMACROS_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_LOGGINGMACROS_HPP

#include <QLoggingCategory>

/**
 * @file loggingMacros.hpp
 *
 * Logging macros. Convenient macros to log messages with Qt logging categories. These macros can be used by other modules
 * providing that they implement loggingCategory() function in their own namespace. This function should return QLoggingCategory
 * object, which is declared and defined with Q_DECLARE_LOGGING_CATEGORY and Q_LOGGING_CATEGORY macros, as described in Qt
 * documentation. Macros are corresponding to Qt debug streams.
 *	- CUTEHMI_DEBUG - debug message (qCDebug()).
 *	- CUTEHMI_INFO - informative message (qCInfo()).
 *	- CUTEHMI_WARNING - informative message (qCWarning()).
 *	- CUTEHMI_CRITICAL - informative message (qCCritical()).
 *	.
 *
 * There's no CUTEHMI_FATAL, because Qt (5.12) does not provide QDebug output stream for fatal errors. Instead CUTEHMI_DIE macro
 * can be used. Unlike the other logging macros CUTEHMI_DIE does not wrap QDebug output stream, so a formatted string should be
 * passed as macro argument (see QMessageLogger::fatal()).
 */

#ifndef CUTEHMI_NDEBUG
	#define CUTEHMI_DEBUG(EXPR) qCDebug(loggingCategory()).nospace().noquote() << EXPR
#else
	#define CUTEHMI_DEBUG(EXPR) (void)0
#endif

#ifndef CUTEHMI_NINFO
	#define CUTEHMI_INFO(EXPR) qCInfo(loggingCategory()).nospace().noquote() << EXPR
#else
	#define CUTEHMI_INFO(EXPR) (void)0
#endif

#ifndef CUTEHMI_NWARNING
	#define CUTEHMI_WARNING(EXPR) qCWarning(loggingCategory()).nospace().noquote() << EXPR
#else
	#define CUTEHMI_WARNING(EXPR) (void)0
#endif

#ifndef CUTEHMI_NCRITICAL
	#define CUTEHMI_CRITICAL(EXPR) qCCritical(loggingCategory()).nospace().noquote() << EXPR
#else
	#define CUTEHMI_CRITICAL(EXPR) (void)0
#endif

#define CUTEHMI_DIE(...) QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, loggingCategory().categoryName()).fatal(__VA_ARGS__)

#ifndef CUTEHMI_NDEBUG
	#define CUTEHMI_ASSERT(EXPR, MSG) Q_ASSERT_X(EXPR, __FILE__, MSG)
#else
	#define CUTEHMI_ASSERT(EXPR, MSG) (void)0
#endif

#endif
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
