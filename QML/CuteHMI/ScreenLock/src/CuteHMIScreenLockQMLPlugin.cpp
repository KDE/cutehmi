#include "CuteHMIScreenLockQMLPlugin.hpp"
#include "cutehmi/screen_lock/PasswordInterface.hpp"

#include <QtQml>

void CuteHMIScreenLockQMLPlugin::registerTypes(const char * uri)
{
    Q_ASSERT(uri == QLatin1String("CuteHMI.ScreenLock"));
    qmlRegisterSingletonType<cutehmi::screen_lock::PasswordInterface>(uri, 1, 0, "PasswordInterface", PasswordInterfaceProvider);
}

QObject * CuteHMIScreenLockQMLPlugin::PasswordInterfaceProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
    Q_UNUSED(scriptEngine)

    cutehmi::screen_lock::PasswordInterface *interface = new cutehmi::screen_lock::PasswordInterface();
    engine->setObjectOwnership(interface, QQmlEngine::CppOwnership);
    return interface;
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
