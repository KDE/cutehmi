#include "QMLPlugin.hpp"

#include <cutehmi/metadata.hpp>
#include <cutehmi/Message.hpp>
#include <cutehmi/Messenger.hpp>
#include <cutehmi/Notification.hpp>
#include <cutehmi/Notifier.hpp>

#include <QtQml>

//<Doxygen-3.workaround target="Doxygen" cause="missing">
#ifdef DOXYGEN_WORKAROUND

namespace CuteHMI {

/**
 * Exposes cutehmi::Message to QML.
 */
class Message: public cutehmi::Message {};

/**
 * Exposes cutehmi::Notification to QML.
 */
class Notification: public cutehmi::Notification {};

/**
 * Exposes cutehmi::Messenger to QML.
 */
class Messenger: public cutehmi::Messenger {};

/**
 * Exposes cutehmi::Notifier to QML.
 */
class Notifier: public cutehmi::Notifier {};

}

#endif
//</Doxygen-3.workaround>

namespace cutehmi {
namespace internal {

/**
 * Register QML types.
 * @param uri URI.
 */
void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI"));

	qmlRegisterType<cutehmi::Message>(uri, CUTEHMI_MAJOR, 0, "Message");
	qmlRegisterType<cutehmi::Notification>(uri, CUTEHMI_MAJOR, 0, "Notification");
	qmlRegisterSingletonType<cutehmi::Messenger>(uri, CUTEHMI_MAJOR, 0, "Messenger", MessengerProvider);
	qmlRegisterSingletonType<cutehmi::Notifier>(uri, CUTEHMI_MAJOR, 0, "Notifier", NotifierProvider);
}

QObject * QMLPlugin::MessengerProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::Messenger * messenger = & cutehmi::Messenger::Instance();
	engine->setObjectOwnership(messenger, QQmlEngine::CppOwnership);
	return messenger;
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

//(c)C: Copyright © 2018-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
