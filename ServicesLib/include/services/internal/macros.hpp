#ifndef CUTEHMI_SERVICESLIB_INCLUDE_SERVICES_INTERNAL_MACROS_HPP
#define CUTEHMI_SERVICESLIB_INCLUDE_SERVICES_INTERNAL_MACROS_HPP

#include <base/macros.hpp>

Q_DECLARE_LOGGING_CATEGORY(lib_cutehmi_services_0_loggingCategory)

#define CUTEHMI_SERVICES_QDEBUG(EXPR) CUTEHMI_BASE_QCDEBUG(lib_cutehmi_services_0_loggingCategory, EXPR)
#define CUTEHMI_SERVICES_QINFO(EXPR) CUTEHMI_BASE_QCINFO(lib_cutehmi_services_0_loggingCategory, EXPR)
#define CUTEHMI_SERVICES_QWARNING(EXPR) CUTEHMI_BASE_QCWARNING(lib_cutehmi_services_0_loggingCategory, EXPR)
#define CUTEHMI_SERVICES_QCRITICAL(EXPR) CUTEHMI_BASE_QCCRITICAL(lib_cutehmi_services_0_loggingCategory, EXPR)

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
