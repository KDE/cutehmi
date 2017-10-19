#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_INTERNAL_MACROS_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_INTERNAL_MACROS_HPP

#include "../macros.hpp"

Q_DECLARE_LOGGING_CATEGORY(cutehmi_base_0_lib_loggingCategory)

#define CUTEHMI_BASE_QDEBUG(EXPR) CUTEHMI_BASE_QCDEBUG(cutehmi_base_0_lib_loggingCategory, EXPR)
#define CUTEHMI_BASE_QINFO(EXPR) CUTEHMI_BASE_QCINFO(cutehmi_base_0_lib_loggingCategory, EXPR)
#define CUTEHMI_BASE_QWARNING(EXPR) CUTEHMI_BASE_QCWARNING(cutehmi_base_0_lib_loggingCategory, EXPR)
#define CUTEHMI_BASE_QCRITICAL(EXPR) CUTEHMI_BASE_QCCRITICAL(cutehmi_base_0_lib_loggingCategory, EXPR)

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
