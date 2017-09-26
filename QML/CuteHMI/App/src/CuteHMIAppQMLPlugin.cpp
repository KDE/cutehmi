#include "CuteHMIAppQMLPlugin.hpp"

#include <app/CuteApp.hpp>

#include <QtQml>

void CuteHMIAppQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.App"));

	//<workaround ref="QML_CuteHMI_LockScreen-1" target="Qt" cause="design">
	qmlRegisterSingletonType<cutehmi::app::CuteApp>(uri, 1, 0, "CuteApp", CuteAppProvider);
	//</workaround>
}

QObject * CuteHMIAppQMLPlugin::CuteAppProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	QObject * cuteApp = cutehmi::app::CuteApp::instance();
	engine->setObjectOwnership(cuteApp, QQmlEngine::CppOwnership);
	return cuteApp;
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
