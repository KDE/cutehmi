#include "QMLPlugin.hpp"

#include <cutehmi/metadata.hpp>
#include <cutehmi/Dialog.hpp>
#include <cutehmi/Dialogist.hpp>
#include <cutehmi/Notification.hpp>
#include <cutehmi/Notifier.hpp>

#include <QtQml>

namespace CuteHMI {

/**
 * @class CuteHMI::Dialog
 * Exposes cutehmi::Dialog to QML.
 */

/**
 * @class CuteHMI::Notificatoin
 * Exposes cutehmi::Notification to QML.
 */

/**
 * @class CuteHMI::Dialogist
 * Exposes cutehmi::Dialogist to QML.
 */

/**
 * @class CuteHMI::Notifier
 * Exposes cutehmi::Notifier to QML.
 */

}


namespace cutehmi {
namespace internal {

/**
 * Register QML types.
 * @param uri URI.
 */
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

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
