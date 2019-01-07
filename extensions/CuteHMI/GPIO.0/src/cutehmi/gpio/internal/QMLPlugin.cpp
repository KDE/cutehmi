#include "QMLPlugin.hpp"

#include <cutehmi/gpio/Chip.hpp>
#include <cutehmi/gpio/Line.hpp>
#include <cutehmi/gpio/LineConfig.hpp>
#include <cutehmi/gpio/ChipEnumerator.hpp>

#include <QtQml>

namespace cutehmi {
namespace gpio {
namespace internal {

void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.GPIO"));

	qmlRegisterType<cutehmi::gpio::Chip>(uri, CUTEHMI_GPIO_MAJOR, 0, "Chip");
	qmlRegisterUncreatableType<cutehmi::gpio::Line>(uri, CUTEHMI_GPIO_MAJOR, 0, "Line", "cutehmi::gpio::Line instance can not be created from QML.");
	qmlRegisterType<cutehmi::gpio::LineConfig>(uri, CUTEHMI_GPIO_MAJOR, 0, "LineConfig");
}

QObject * QMLPlugin::ChipEnumeratorProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	gpio::ChipEnumerator * enumerator = & gpio::ChipEnumerator::Instance();
	engine->setObjectOwnership(enumerator, QQmlEngine::CppOwnership);
	return enumerator;
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
