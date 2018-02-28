#include "CuteHMIQMLPlugin.hpp"

#include <cutehmi/CuteHMI.hpp>
#include <cutehmi/Prompt.hpp>
#include <cutehmi/Notification.hpp>

#include <QtQml>

void CuteHMIQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI"));

	qmlRegisterType<cutehmi::Prompt>(uri, 1, 0, "Prompt");
	qmlRegisterType<cutehmi::Notification>(uri, 1, 0, "Notification");
	qmlRegisterUncreatableType<cutehmi::PopupBridge>(uri, 1, 0, "PopupBridge", QObject::tr("cutehmi::PopupBridge instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::NotificationManager>(uri, 1, 0, "NotificationManager", QObject::tr("cutehmi::NotificationManager instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::Project>(uri, 1, 0, "Project", QObject::tr("cutehmi::Project instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::ProjectModel>(uri, 1, 0, "ProjectModel", QObject::tr("cutehmi::ProjectModel instances can not be created within QML."));
	qmlRegisterUncreatableType<const cutehmi::ProjectNode>(uri, 1, 0, "ProjectNode", QObject::tr("cutehmi::ProjectNode instances can not be created within QML."));
	qmlRegisterSingletonType<cutehmi::CuteHMI>(uri, 1, 0, "CuteHMI", CuteHMIProvider);
}

QObject * CuteHMIQMLPlugin::CuteHMIProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::CuteHMI * cuteHMI = & cutehmi::CuteHMI::Instance();
	engine->setObjectOwnership(cuteHMI, QQmlEngine::CppOwnership);
	return cuteHMI;
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
