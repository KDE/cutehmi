#include "CuteHMILockScreenQMLPlugin.hpp"
#include "cutehmi/lock_screen/Auth.hpp"
#include "cutehmi/lock_screen/InternalSettings.hpp"

#include <QtQml>

#include <memory>

void CuteHMILockScreenQMLPlugin::registerTypes(const char * uri)
{
    Q_ASSERT(uri == QLatin1String("CuteHMI.LockScreen"));
    qmlRegisterSingletonType<cutehmi::lockscreen::Auth>(uri, 1, 0, "Auth", AuthProvider);
	qmlRegisterSingletonType<cutehmi::lockscreen::InternalSettings>(uri, 1, 0, "Settings", InternalSettingsProvider);
}

QObject * CuteHMILockScreenQMLPlugin::AuthProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
    Q_UNUSED(scriptEngine)
    Q_UNUSED(engine)

    std::unique_ptr<cutehmi::lockscreen::Auth> instance(new cutehmi::lockscreen::Auth);
    return instance.release();
}

QObject * CuteHMILockScreenQMLPlugin::InternalSettingsProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)
	Q_UNUSED(engine)

	std::unique_ptr<cutehmi::lockscreen::InternalSettings> instance(new cutehmi::lockscreen::InternalSettings);
	return instance.release();
}
