#ifndef CUTEHMI_APPPLUGIN_SRC_APP_PLUGIN_MACROS_HPP
#define CUTEHMI_APPPLUGIN_SRC_APP_PLUGIN_MACROS_HPP

#include <base/macros.hpp>

Q_DECLARE_LOGGING_CATEGORY(cutehmi_app_plugin_loggingCategory)

#define CUTEHMI_APP_PLUGIN_QDEBUG(EXPR) CUTEHMI_BASE_QCDEBUG(cutehmi_app_plugin_loggingCategory, EXPR)
#define CUTEHMI_APP_PLUGIN_QINFO(EXPR) CUTEHMI_BASE_QCINFO(cutehmi_app_plugin_loggingCategory, EXPR)
#define CUTEHMI_APP_PLUGIN_QWARNING(EXPR) CUTEHMI_BASE_QCWARNING(cutehmi_app_plugin_loggingCategory, EXPR)
#define CUTEHMI_APP_PLUGIN_QCRITICAL(EXPR) CUTEHMI_BASE_QCCRITICAL(cutehmi_app_plugin_loggingCategory, EXPR)

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
