#include "QMLPlugin.hpp"

#include <cutehmi/app/CuteApp.hpp>

#include <QtQml>

namespace CuteHMI {
namespace App {

/**
 * @class CuteHMI::App::CuteApp
 * Exposes cutehmi::app::CuteApp to QML.
 */

}
}

namespace cutehmi {
namespace app {
namespace internal {

/**
 * Register QML types.
 * @param uri URI.
 */
void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.App"));

	//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
	qmlRegisterSingletonType<cutehmi::app::CuteApp>(uri, CUTEHMI_APP_MAJOR, 0, "CuteApp", CuteAppProvider);
	//</CuteHMI.LockScreen-1.workaround>
}

QObject * QMLPlugin::CuteAppProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	QObject * cuteApp = cutehmi::app::CuteApp::instance();
	engine->setObjectOwnership(cuteApp, QQmlEngine::CppOwnership);
	return cuteApp;
}

}
}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
