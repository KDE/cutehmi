#include <cutehmi/gui/Theme.hpp>

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

Palette & Theme::DefaultPalette()
{
	static Palette palette;
	static ColorSet alarm;
	static ColorSet warning;
	static ColorSet active;
	static ColorSet inactive;
	static ColorSet neutral;

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

	return palette;
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
