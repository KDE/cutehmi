#include "CuteHMIBaseQMLPlugin.hpp"

#include <cutehmi/CuteHMI.hpp>
#include <cutehmi/Prompt.hpp>
#include <cutehmi/Notification.hpp>

#include <QtQml>

void CuteHMIBaseQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Base"));

	qmlRegisterType<cutehmi::base::Prompt>(uri, 1, 0, "Prompt");
	qmlRegisterType<cutehmi::base::Notification>(uri, 1, 0, "Notification");
	qmlRegisterUncreatableType<cutehmi::base::PopupBridge>(uri, 1, 0, "PopupBridge", QObject::tr("cutehmi::base::PopupBridge instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::base::NotificationManager>(uri, 1, 0, "NotificationManager", QObject::tr("cutehmi::base::NotificationManager instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::base::Project>(uri, 1, 0, "Project", QObject::tr("cutehmi::base::Project instances can not be created within QML."));
	qmlRegisterUncreatableType<cutehmi::base::ProjectModel>(uri, 1, 0, "ProjectModel", QObject::tr("cutehmi::base::ProjectModel instances can not be created within QML."));
	qmlRegisterUncreatableType<const cutehmi::base::ProjectNode>(uri, 1, 0, "ProjectNode", QObject::tr("cutehmi::base::ProjectNode instances can not be created within QML."));
	qmlRegisterSingletonType<cutehmi::base::CuteHMI>(uri, 1, 0, "CuteHMI", CuteHMIProvider);
}

QObject * CuteHMIBaseQMLPlugin::CuteHMIProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::base::CuteHMI * cuteHMI = & cutehmi::base::CuteHMI::Instance();
	engine->setObjectOwnership(cuteHMI, QQmlEngine::CppOwnership);
	return cuteHMI;
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
