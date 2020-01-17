#include <cutehmi/gui/Palette.hpp>

namespace cutehmi {
namespace gui {

Palette::Palette(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

QColor Palette::background() const
{
	return m->background;
}

void Palette::setBackground(QColor background)
{
	if (m->background != background) {
		m->background = background;
		emit backgroundChanged();
	}
}

ColorSet * Palette::alarm() const
{
	return m->alarm;
}

void Palette::setAlarm(ColorSet * alarm)
{
	if (m->alarm != alarm) {
		m->alarm = alarm;
		emit alarmChanged();
	}
}

ColorSet * Palette::warning() const
{
	return m->warning;
}

void Palette::setWarning(ColorSet * warning)
{
	if (m->warning != warning) {
		m->warning = warning;
		emit warningChanged();
	}
}

ColorSet * Palette::active() const
{
	return m->active;
}

void Palette::setActive(ColorSet * active)
{
	if (m->active != active) {
		m->active = active;
		emit activeChanged();
	}
}

ColorSet * Palette::inactive() const
{
	return m->inactive;
}

void Palette::setInactive(ColorSet * inactive)
{
	if (m->inactive != inactive) {
		m->inactive = inactive;
		emit inactiveChanged();
	}
}

ColorSet * Palette::neutral() const
{
	return m->neutral;
}

void Palette::setNeutral(ColorSet * neutral)
{
	if (m->neutral != neutral) {
		m->neutral = neutral;
		emit neutralChanged();
	}
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
