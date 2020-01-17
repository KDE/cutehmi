#include <cutehmi/gui/Theme.hpp>

//<CuteHMI.GUI-2.workaround target="Qt" cause="bug">
#include <QFontDatabase>
//</CuteHMI.GUI-2.workaround>

namespace cutehmi {
namespace gui {

Theme::Theme(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

Palette * Theme::palette() const
{
	return m->palette;
}

void Theme::setPalette(Palette * palette)
{
	if (m->palette != palette) {
		m->palette = palette;
		emit paletteChanged();
	}
}

void Theme::resetPalette()
{
	m->palette = & DefaultPalette();
}

Units * Theme::units() const
{
	return m->units;
}

void Theme::setUnits(Units * units)
{
	if (m->units != units) {
		m->units = units;
		emit unitsChanged();
	}
}

void Theme::resetUnits()
{
	m->units = & DefaultUnits();
}

Fonts * Theme::fonts() const
{
	return m->fonts;
}

void Theme::setFonts(Fonts * fonts)
{
	if (m->fonts != fonts) {
		m->fonts = fonts;
		emit fontsChanged();
	}
}

void Theme::resetFonts()
{
	m->fonts = & DefaultFonts();
}

Palette & Theme::DefaultPalette()
{
	static Palette palette;
	static ColorSet alarm;
	static ColorSet warning;
	static ColorSet active;
	static ColorSet inactive;
	static ColorSet neutral;
	static bool initialized = false;

	if (!initialized) {
		palette.setBackground("white");

		alarm.setBase("#FF3300");
		alarm.setFill(alarm.base());
		alarm.setTint("#FF4B1D");
		alarm.setShade(alarm.base().darker());
		alarm.setForeground("black");
		alarm.setBackground(alarm.tint());
		alarm.setStroke("black");
		palette.setAlarm(& alarm);

		warning.setBase("#FF9933");
		warning.setFill(warning.base());
		warning.setTint("#FFA64D");
		warning.setShade(warning.base().darker());
		warning.setForeground("black");
		warning.setBackground(warning.tint());
		warning.setStroke("black");
		palette.setWarning(& warning);

		active.setBase("#66CC33");
		active.setFill(active.base());
		active.setTint("#CCF4CC");
		active.setShade(active.base().darker());
		active.setForeground("black");
		active.setBackground(active.tint());
		active.setStroke("black");
		palette.setActive(& active);

		inactive.setBase("#CECECE");
		inactive.setFill(inactive.base());
		inactive.setTint("#E3E3E3");
		inactive.setShade(inactive.base().darker());
		inactive.setForeground("black");
		inactive.setBackground(inactive.tint());
		inactive.setStroke("black");
		palette.setInactive(& inactive);

		neutral.setBase("black");
		neutral.setFill("white");
		neutral.setTint(neutral.base().lighter());
		neutral.setShade(neutral.base().darker());
		neutral.setForeground("black");
		neutral.setBackground("white");
		neutral.setStroke("black");
		palette.setNeutral(& neutral);
	}

	return palette;
}

Units & Theme::DefaultUnits()
{
	static Units units;
	return units;
}

Fonts & Theme::DefaultFonts()
{
	static Fonts fonts;
	static bool initialized = false;

	if (!initialized) {
		QFont monospace;

		//<CuteHMI.GUI-2.workaround target="Qt" cause="bug">
		// Look for available monospace family manually.
		QFontDatabase fontDatabase;
		QStringList availableFamilies = fontDatabase.families();
		QStringList monospaceFamilies({"Droid Sans Mono",
						"Lucida Console",
						"Ubuntu Mono",
						"Liberation Mono",
						"Courier New"});
		QString monospaceFamily;
		for (auto it = monospaceFamilies.begin(); it != monospaceFamilies.end(); ++it)
			if (availableFamilies.contains(*it)) {
				monospaceFamily = *it;
				break;
			}
		//</CuteHMI.GUI-2.workaround>

		if (!monospaceFamily.isNull())
			monospace.setFamily(monospaceFamily);
		fonts.setMonospace(monospace);

		initialized = true;
	}

	return fonts;
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
