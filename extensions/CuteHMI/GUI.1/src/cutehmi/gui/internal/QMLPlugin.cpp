#include "QMLPlugin.hpp"

#include <cutehmi/gui/CuteApplication.hpp>
#include <cutehmi/gui/ColorSet.hpp>
#include <cutehmi/gui/Palette.hpp>
#include <cutehmi/gui/Fonts.hpp>
#include <cutehmi/gui/Units.hpp>
#include <cutehmi/gui/Theme.hpp>

#include <QtQml>

//<Doxygen-3.workaround target="Doxygen" cause="missing">
#ifdef DOXYGEN_WORKAROUND

namespace CuteHMI {
namespace GUI {

/**
 * Exposes cutehmi::gui::CuteApplication to QML.
 */
class CuteApplication: public cutehmi::gui::CuteApplication {};

/**
 * Exposes cutehmi::gui::ColorSet to QML.
 */
class ColorSet: public cutehmi::gui::ColorSet {};

/**
 * Exposes cutehmi::gui::Palette to QML.
 */
class Palette: public cutehmi::gui::Palette  {};

/**
 * Exposes cutehmi::gui::Fonts to QML.
 */
class Fonts: public cutehmi::gui::Fonts {};

/**
 * Exposes cutehmi::gui::Units to QML.
 */
class Units: public cutehmi::gui::Units {};

/**
 * Exposes cutehmi::gui::Theme to QML.
 */
class Theme: public cutehmi::gui::Theme {};

}
}

#endif
//</Doxygen-3.workaround>

namespace cutehmi {
namespace gui {
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
	// @uri CuteHMI.GUI
	qmlRegisterSingletonType<cutehmi::gui::Theme>(uri, CUTEHMI_GUI_MAJOR, 0, "Theme", ThemeProvider);

	if (!qEnvironmentVariableIsSet("QML_PUPPET_MODE")) {
		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		// @uri CuteHMI.GUI
		qmlRegisterSingletonType<cutehmi::gui::CuteApplication>(uri, CUTEHMI_GUI_MAJOR, 0, "CuteApplication", CuteApplicationProvider);
		//</CuteHMI.LockScreen-1.workaround>
	}
}

QObject * QMLPlugin::CuteApplicationProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	QObject * app = cutehmi::gui::CuteApplication::instance();
	engine->setObjectOwnership(app, QQmlEngine::CppOwnership);
	return app;
}

QObject * QMLPlugin::ThemeProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	QObject * theme = & cutehmi::gui::Theme::Instance();
	engine->setObjectOwnership(theme, QQmlEngine::CppOwnership);
	return theme;
}

#endif
//</CuteHMI.Workarounds.Qt5Compatibility-4.workaround>

}
}
}

//(c)C: Copyright © 2020-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
