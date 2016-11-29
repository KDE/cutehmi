#include "CuteHMIChartsQMLPlugin.hpp"
#include "charts/ScatterPlot.hpp"
#include "charts/LinearAxis.hpp"
#include "charts/DateTimeAxis.hpp"
#include "charts/PlotArea.hpp"

#include <charts/PointSeries.hpp>

#include <QtQml>

void CuteHMIChartsQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Charts"));
	qmlRegisterType<cutehmi::charts::ScatterPlot>(uri, 1, 0, "PointSeries");
	qmlRegisterType<cutehmi::charts::ScatterPlot>(uri, 1, 0, "ScatterPlot");
	qmlRegisterType<cutehmi::charts::ValueAxis>();
	qmlRegisterType<cutehmi::charts::CartesianAxis>();
	qmlRegisterType<cutehmi::charts::TickedAxis>();
	qmlRegisterType<cutehmi::charts::LinearAxis>(uri, 1, 0, "LinearAxis");
	qmlRegisterType<cutehmi::charts::DateTimeAxis>(uri, 1, 0, "DateTimeAxis");
	qmlRegisterType<cutehmi::charts::PlotArea>(uri, 1, 0, "PlotArea");
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
