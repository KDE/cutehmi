#include "CuteHMIQMLPlugin.hpp"

#include <cutehmi/CuteHMI.hpp>
#include <cutehmi/Prompt.hpp>
#include <cutehmi/Notification.hpp>

#include <QtQml>

void CuteHMIQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI"));

	qmlRegisterType<cutehmi::Prompt>(uri, CUTEHMI_MAJOR, CUTEHMI_1_CURRENT, "Prompt");
	qmlRegisterType<cutehmi::Notification>(uri, CUTEHMI_MAJOR, CUTEHMI_1_CURRENT, "Notification");
	qmlRegisterUncreatableType<cutehmi::PopupBridge>(uri, CUTEHMI_MAJOR, CUTEHMI_1_CURRENT, "PopupBridge", QObject::tr("cutehmi::PopupBridge instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::NotificationManager>(uri, CUTEHMI_MAJOR, CUTEHMI_1_CURRENT, "NotificationManager", QObject::tr("cutehmi::NotificationManager instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::Project>(uri, CUTEHMI_MAJOR, CUTEHMI_1_CURRENT, "Project", QObject::tr("cutehmi::Project instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::ProjectModel>(uri, CUTEHMI_MAJOR, CUTEHMI_1_CURRENT, "ProjectModel", QObject::tr("cutehmi::ProjectModel instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::Plugin>(uri, CUTEHMI_MAJOR, CUTEHMI_1_CURRENT, "Plugin", QObject::tr("cutehmi::Plugin instances can not be created within QML."));
	qmlRegisterUncreatableType<const cutehmi::ProjectNode>(uri, CUTEHMI_MAJOR, CUTEHMI_1_CURRENT, "ProjectNode", QObject::tr("cutehmi::ProjectNode instances can not be created within QML."));
	qmlRegisterSingletonType<cutehmi::CuteHMI>(uri, CUTEHMI_MAJOR, CUTEHMI_1_CURRENT, "CuteHMI", CuteHMIProvider);
}

QObject * CuteHMIQMLPlugin::CuteHMIProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::CuteHMI * cuteHMI = & cutehmi::CuteHMI::Instance();
	engine->setObjectOwnership(cuteHMI, QQmlEngine::CppOwnership);
	return cuteHMI;
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
