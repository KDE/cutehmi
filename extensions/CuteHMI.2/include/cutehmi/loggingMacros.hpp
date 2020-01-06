#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_LOGGINGMACROS_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_LOGGINGMACROS_HPP

#include <QLoggingCategory>

/**
 * @defgroup cutehmi-loggingMacros Logging macros
 *
 * Logging macros.
 *
 * Convenient macros to log messages with Qt logging categories. These macros can be used by other modules providing that they
 * implement loggingCategory() function in their own namespace. This function should return QLoggingCategory object, which is
 * declared and defined with Q_DECLARE_LOGGING_CATEGORY and Q_LOGGING_CATEGORY macros, as described in Qt documentation. Macros are
 * corresponding to Qt debug streams.
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
///@{

/**
  @def CUTEHMI_DEBUG(EXPR)
  Print debug message.
  @param EXPR message (can be composed of stream expression).
  */
#ifndef CUTEHMI_NDEBUG
	#define CUTEHMI_DEBUG(EXPR) qCDebug(loggingCategory()).nospace().noquote() << EXPR
#else
	#define CUTEHMI_DEBUG(EXPR) (void)0
#endif

/**
  @def CUTEHMI_INFO(EXPR)
  Print informative message.
  @param EXPR message (can be composed of stream expression).
  */
#ifndef CUTEHMI_NINFO
	#define CUTEHMI_INFO(EXPR) qCInfo(loggingCategory()).nospace().noquote() << EXPR
#else
	#define CUTEHMI_INFO(EXPR) (void)0
#endif

/**
  @def CUTEHMI_WARNING(EXPR)
  Print warning.
  @param EXPR message (can be composed of stream expression).
  */
#ifndef CUTEHMI_NWARNING
	#define CUTEHMI_WARNING(EXPR) qCWarning(loggingCategory()).nospace().noquote() << EXPR
#else
	#define CUTEHMI_WARNING(EXPR) (void)0
#endif

/**
  @def CUTEHMI_CRITICAL(EXPR)
  Print critical message.
  @param EXPR message (can be composed of stream expression).
  */
#ifndef CUTEHMI_NCRITICAL
	#define CUTEHMI_CRITICAL(EXPR) qCCritical(loggingCategory()).nospace().noquote() << EXPR
#else
	#define CUTEHMI_CRITICAL(EXPR) (void)0
#endif

/**
  @def CUTEHMI_DIE(...)
  Print fatal message and abort or exit program.
  @param ... fatal message and optional list of arguments interpreted by message format string.
  */
#define CUTEHMI_DIE(...) QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, loggingCategory().categoryName()).fatal(__VA_ARGS__)

/**
  @def CUTEHMI_ASSERT(EXPR, MSG)
  Assert.
  @param EXPR assert expression
  @param MSG message printed in case of assertion failure.
  */
#ifndef CUTEHMI_NDEBUG
	#define CUTEHMI_ASSERT(EXPR, MSG) Q_ASSERT_X(EXPR, __FILE__, MSG)
#else
	#define CUTEHMI_ASSERT(EXPR, MSG) (void)0
#endif

///@}

#endif

//(c)C: Copyright © 2018-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
