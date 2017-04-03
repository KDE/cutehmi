#ifndef CUTEHMI_LIBCHARTS_INCLUDE_CHARTS_INTERNAL_MACROS_HPP
#define CUTEHMI_LIBCHARTS_INCLUDE_CHARTS_INTERNAL_MACROS_HPP

#include <base/macros.hpp>

Q_DECLARE_LOGGING_CATEGORY(cutehmi_charts_loggingCategory)

#define CUTEHMI_CHARTS_QDEBUG(EXPR) CUTEHMI_BASE_QCDEBUG(cutehmi_charts_loggingCategory, EXPR)
#define CUTEHMI_CHARTS_QINFO(EXPR) CUTEHMI_BASE_QCINFO(cutehmi_charts_loggingCategory, EXPR)
#define CUTEHMI_CHARTS_QWARNING(EXPR) CUTEHMI_BASE_QCWARNING(cutehmi_charts_loggingCategory, EXPR)
#define CUTEHMI_CHARTS_QCRITICAL(EXPR) CUTEHMI_BASE_QCCRITICAL(cutehmi_charts_loggingCategory, EXPR)

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
