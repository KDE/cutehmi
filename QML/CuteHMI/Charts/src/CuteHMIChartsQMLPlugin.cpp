#include "CuteHMIChartsQMLPlugin.hpp"
#include "cutehmi/charts/qml/ScatterPlot.hpp"
#include "cutehmi/charts/qml/LinearAxis.hpp"
#include "cutehmi/charts/qml/DateTimeAxis.hpp"
#include "cutehmi/charts/qml/PlotArea.hpp"

#include <cutehmi/charts/PointSeries.hpp>

#include <QtQml>

void CuteHMIChartsQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Charts"));
	qmlRegisterType<cutehmi::charts::qml::ScatterPlot>(uri, 1, 0, "PointSeries");
	qmlRegisterType<cutehmi::charts::qml::ScatterPlot>(uri, 1, 0, "ScatterPlot");
	qmlRegisterType<cutehmi::charts::qml::ValueAxis>();
	qmlRegisterType<cutehmi::charts::qml::CartesianAxis>();
	qmlRegisterType<cutehmi::charts::qml::TickedAxis>();
	qmlRegisterType<cutehmi::charts::qml::LinearAxis>(uri, 1, 0, "LinearAxis");
	qmlRegisterType<cutehmi::charts::qml::DateTimeAxis>(uri, 1, 0, "DateTimeAxis");
	qmlRegisterType<cutehmi::charts::qml::PlotArea>(uri, 1, 0, "PlotArea");
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
