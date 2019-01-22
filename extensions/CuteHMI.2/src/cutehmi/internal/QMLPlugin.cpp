#include "QMLPlugin.hpp"

#include <cutehmi/metadata.hpp>
#include <cutehmi/Dialog.hpp>
#include <cutehmi/Dialogist.hpp>
#include <cutehmi/Notification.hpp>
#include <cutehmi/Notifier.hpp>

#include <QtQml>

namespace cutehmi {
namespace internal {

void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI"));

	qmlRegisterType<cutehmi::Dialog>(uri, CUTEHMI_MAJOR, 0, "Dialog");
	qmlRegisterType<cutehmi::Notification>(uri, CUTEHMI_MAJOR, 0, "Notification");
	qmlRegisterSingletonType<cutehmi::Dialogist>(uri, CUTEHMI_MAJOR, 0, "Dialogist", DialogistProvider);
	qmlRegisterSingletonType<cutehmi::Notifier>(uri, CUTEHMI_MAJOR, 0, "Notifier", NotifierProvider);
}

QObject * QMLPlugin::DialogistProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::Dialogist * dialogist = & cutehmi::Dialogist::Instance();
	engine->setObjectOwnership(dialogist, QQmlEngine::CppOwnership);
	return dialogist;
}

QObject * QMLPlugin::NotifierProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::Notifier * notifier = & cutehmi::Notifier::Instance();
	engine->setObjectOwnership(notifier, QQmlEngine::CppOwnership);
	return notifier;
}

}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
