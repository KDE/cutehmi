#include <cutehmi/gui/Palette.hpp>

namespace cutehmi {
namespace gui {

constexpr Qt::GlobalColor Palette::INITIAL_BACKGROUND;

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

void Palette::resetAlarm()
{
	m->alarm = & DefaultAlarm();
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

void Palette::resetWarning()
{
	m->warning = & DefaultWarning();
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

void Palette::resetActive()
{
	m->active = & DefaultActive();
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

void Palette::resetInactive()
{
	m->inactive = & DefaultInactive();
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

void Palette::resetNeutral()
{
	m->neutral = & DefaultNeutral();
}

ColorSet & Palette::DefaultAlarm()
{
	static ColorSet alarm;

	alarm.setBase("#FF3300");	// clazy:exclude=qcolor-from-literal
	alarm.setFill(alarm.base());
	alarm.setTint("#FF4B1D");	// clazy:exclude=qcolor-from-literal
	alarm.setShade(alarm.base().darker());
	alarm.setForeground("black");
	alarm.setBackground(alarm.tint());
	alarm.setStroke("black");
	alarm.setBlank(INITIAL_BACKGROUND);

	return alarm;
}

ColorSet & Palette::DefaultWarning()
{
	static ColorSet warning;

	warning.setBase("#FF9933");	// clazy:exclude=qcolor-from-literal
	warning.setFill(warning.base());
	warning.setTint("#FFA64D");	// clazy:exclude=qcolor-from-literal
	warning.setShade(warning.base().darker());
	warning.setForeground("black");
	warning.setBackground(warning.tint());
	warning.setStroke("black");
	warning.setBlank(INITIAL_BACKGROUND);

	return warning;
}

ColorSet & Palette::DefaultActive()
{
	static ColorSet active;

	active.setBase("#66CC33");	// clazy:exclude=qcolor-from-literal
	active.setFill(active.base());
	active.setTint("#CCF4CC");	// clazy:exclude=qcolor-from-literal
	active.setShade(active.base().darker());
	active.setForeground("black");
	active.setBackground(active.tint());
	active.setStroke("black");
	active.setBlank(INITIAL_BACKGROUND);

	return active;
}

ColorSet & Palette::DefaultInactive()
{
	static ColorSet inactive;

	inactive.setBase("#CECECE");	// clazy:exclude=qcolor-from-literal
	inactive.setFill(inactive.base());
	inactive.setTint("#E3E3E3");	// clazy:exclude=qcolor-from-literal
	inactive.setShade(inactive.base().darker());
	inactive.setForeground("black");
	inactive.setBackground(inactive.tint());
	inactive.setStroke("black");
	inactive.setBlank(INITIAL_BACKGROUND);

	return inactive;
}

ColorSet & Palette::DefaultNeutral()
{
	static ColorSet neutral;

	neutral.setBase("black");
	neutral.setFill("white");
	neutral.setTint(neutral.base().lighter());
	neutral.setShade(neutral.base().darker());
	neutral.setForeground("black");
	neutral.setBackground("white");
	neutral.setStroke("black");
	neutral.setBlank(INITIAL_BACKGROUND);

	return neutral;
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
