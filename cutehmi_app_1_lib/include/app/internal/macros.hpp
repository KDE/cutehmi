#ifndef CUTEHMI_CUTEHMI__APP__1__LIB_INCLUDE_APP_INTERNAL_MACROS_HPP
#define CUTEHMI_CUTEHMI__APP__1__LIB_INCLUDE_APP_INTERNAL_MACROS_HPP

#include <base/macros.hpp>

Q_DECLARE_LOGGING_CATEGORY(cutehmi_app_1_lib_loggingCategory)

#define CUTEHMI_APP_QDEBUG(EXPR) CUTEHMI_APP_QCDEBUG(cutehmi_app_1_lib_loggingCategory, EXPR)
#define CUTEHMI_APP_QINFO(EXPR) CUTEHMI_APP_QCINFO(cutehmi_app_1_lib_loggingCategory, EXPR)
#define CUTEHMI_APP_QWARNING(EXPR) CUTEHMI_APP_QCWARNING(cutehmi_app_1_lib_loggingCategory, EXPR)
#define CUTEHMI_APP_QCRITICAL(EXPR) CUTEHMI_APP_QCCRITICAL(cutehmi_app_1_lib_loggingCategory, EXPR)

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
