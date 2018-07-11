#include "CuteHMILockScreenQMLPlugin.hpp"
#include "cutehmi/lockscreen/qml/Auth.hpp"
#include "cutehmi/lockscreen/qml/Settings.hpp"

#include <QtQml>

#include <memory>

void CuteHMILockScreenQMLPlugin::registerTypes(const char * uri)
{
    Q_ASSERT(uri == QLatin1String("CuteHMI.LockScreen"));
	qmlRegisterSingletonType<cutehmi::lockscreen::qml::Auth>(uri, 1, 0, "Auth", AuthProvider);
	qmlRegisterSingletonType<cutehmi::lockscreen::qml::Settings>(uri, 1, 0, "Settings", SettingsProvider);
}

QObject * CuteHMILockScreenQMLPlugin::AuthProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
    Q_UNUSED(scriptEngine)
    Q_UNUSED(engine)

	std::unique_ptr<cutehmi::lockscreen::qml::Auth> instance(new cutehmi::lockscreen::qml::Auth);
    return instance.release();
}

QObject * CuteHMILockScreenQMLPlugin::SettingsProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)
	Q_UNUSED(engine)

	std::unique_ptr<cutehmi::lockscreen::qml::Settings> instance(new cutehmi::lockscreen::qml::Settings);
	return instance.release();
}

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
