#include "CuteHMILockScreenQMLPlugin.hpp"
#include "cutehmi/lock_screen/Auth.hpp"

#include <QtQml>

void CuteHMILockScreenQMLPlugin::registerTypes(const char * uri)
{
    Q_ASSERT(uri == QLatin1String("CuteHMI.LockScreen"));
    qmlRegisterSingletonType<cutehmi::lockscreen::Auth>(uri, 1, 0, "Auth", AuthProvider);
}

QObject * CuteHMILockScreenQMLPlugin::AuthProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
    Q_UNUSED(scriptEngine)

    cutehmi::lockscreen::Auth *interface = new cutehmi::lockscreen::Auth();
    engine->setObjectOwnership(interface, QQmlEngine::CppOwnership);
    return interface;
}
