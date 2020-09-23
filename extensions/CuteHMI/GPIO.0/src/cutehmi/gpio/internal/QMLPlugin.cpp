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

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
