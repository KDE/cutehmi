#include "QMLPlugin.hpp"

#include "metadata.hpp"
#include "Message.hpp"
#include "Messenger.hpp"
#include "Notification.hpp"
#include "Notifier.hpp"
#include "Internationalizer.hpp"

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

/**
 * Exposes cutehmi::Internationalizer to QML.
 */
class Internationalizer: public cutehmi::Internationalizer {};

}

#endif
//</Doxygen-3.workaround>

namespace cutehmi {
namespace internal {

//<CuteHMI.Workarounds.Qt5Compatibility-4.workaround target="Qt" cause="Qt5.15-QML_SINGLETON">
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#else

/**
 * Register QML types.
 * @param uri URI.
 */
void QMLPlugin::registerTypes(const char * uri)
{
	// @uri CuteHMI
	qmlRegisterSingletonType<cutehmi::Messenger>(uri, CUTEHMI_MAJOR, 0, "Messenger", MessengerProvider);
	qmlRegisterSingletonType<cutehmi::Notifier>(uri, CUTEHMI_MAJOR, 0, "Notifier", NotifierProvider);
	qmlRegisterSingletonType<cutehmi::Internationalizer>(uri, CUTEHMI_MAJOR, 0, "Internationalizer", InternationalizationProvider);
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

QObject * QMLPlugin::InternationalizationProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::Internationalizer * i18ner = & cutehmi::Internationalizer::Instance();
	engine->setObjectOwnership(i18ner, QQmlEngine::CppOwnership);
	return i18ner;
}

#endif
//</CuteHMI.Workarounds.Qt5Compatibility-4.workaround>

}
}

//(c)C: Copyright © 2018-2023, Michał Policht <michal@policht.pl>, Yuri Chornoivan <yurchor@ukr.net>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
