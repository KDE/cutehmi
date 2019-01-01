#include "QMLPlugin.hpp"

#include <cutehmi/CuteHMI.hpp>
#include <cutehmi/Prompt.hpp>
#include <cutehmi/Notification.hpp>

#include <QtQml>

namespace cutehmi {
namespace internal {

void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI"));

	qmlRegisterType<cutehmi::Prompt>(uri, CUTEHMI_MAJOR, 0, "Prompt");
	qmlRegisterType<cutehmi::Notification>(uri, CUTEHMI_MAJOR, 0, "Notification");
	qmlRegisterUncreatableType<cutehmi::PopupBridge>(uri, CUTEHMI_MAJOR, 0, "PopupBridge", QObject::tr("cutehmi::PopupBridge instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::NotificationManager>(uri, CUTEHMI_MAJOR, 0, "NotificationManager", QObject::tr("cutehmi::NotificationManager instances can not be created within QML."));
	qmlRegisterSingletonType<cutehmi::CuteHMI>(uri, CUTEHMI_MAJOR, 0, "CuteHMI", CuteHMIProvider);
}

QObject * QMLPlugin::CuteHMIProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::CuteHMI * cuteHMI = & cutehmi::CuteHMI::Instance();
	engine->setObjectOwnership(cuteHMI, QQmlEngine::CppOwnership);
	return cuteHMI;
}

}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
