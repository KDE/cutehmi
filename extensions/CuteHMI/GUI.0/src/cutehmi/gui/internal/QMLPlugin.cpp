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

/**
 * Register QML types.
 * @param uri URI.
 */
void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.GUI"));

	qmlRegisterType<cutehmi::gui::ColorSet>(uri, CUTEHMI_GUI_MAJOR, 0, "ColorSet");
	qmlRegisterType<cutehmi::gui::Palette>(uri, CUTEHMI_GUI_MAJOR, 0, "Palette");
	qmlRegisterType<cutehmi::gui::Fonts>(uri, CUTEHMI_GUI_MAJOR, 0, "Fonts");
	qmlRegisterType<cutehmi::gui::Units>(uri, CUTEHMI_GUI_MAJOR, 0, "Units");
	qmlRegisterType<cutehmi::gui::Theme>(uri, CUTEHMI_GUI_MAJOR, 0, "Theme");

	if (qgetenv("QML_PUPPET_MODE").isNull()) {
		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
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

}
}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
