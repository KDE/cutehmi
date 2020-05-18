#include <cutehmi/gui/Theme.hpp>

//<CuteHMI.GUI-2.workaround target="Qt" cause="bug">
#include <QFontDatabase>
//</CuteHMI.GUI-2.workaround>

namespace cutehmi {
namespace gui {

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

Theme::Theme(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

Palette & Theme::DefaultPalette()
{
	static Palette palette;
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
	return fonts;
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
