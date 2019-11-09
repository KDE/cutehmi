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

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
