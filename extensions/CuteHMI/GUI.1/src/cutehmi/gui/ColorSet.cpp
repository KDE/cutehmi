#include <cutehmi/gui/ColorSet.hpp>

namespace cutehmi {
namespace gui {

ColorSet::ColorSet(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

QColor ColorSet::base() const
{
	return m->base;
}

void ColorSet::setBase(QColor base)
{
	if (m->base != base) {
		m->base = base;
		emit baseChanged();
	}
}

QColor ColorSet::fill() const
{
	return m->fill;
}

void ColorSet::setFill(QColor fill)
{
	if (m->fill != fill) {
		m->fill = fill;
		emit fillChanged();
	}
}

QColor ColorSet::tint() const
{
	return m->tint;
}

void ColorSet::setTint(QColor tint)
{
	if (m->tint != tint) {
		m->tint = tint;
		emit tintChanged();
	}
}

QColor ColorSet::shade() const
{
	return m->shade;
}

void ColorSet::setShade(QColor shade)
{
	if (m->shade != shade) {
		m->shade = shade;
		emit shadeChanged();
	}
}

QColor ColorSet::background() const
{
	return m->background;
}

void ColorSet::setBackground(QColor background)
{
	if (m->background != background) {
		m->background = background;
		emit backgroundChanged();
	}
}

QColor ColorSet::foreground() const
{
	return m->foreground;
}

void ColorSet::setForeground(QColor foreground)
{
	if (m->foreground != foreground) {
		m->foreground = foreground;
		emit foregroundChanged();
	}
}

QColor ColorSet::stroke() const
{
	return m->stroke;
}

void ColorSet::setStroke(QColor stroke)
{
	if (m->stroke != stroke) {
		m->stroke = stroke;
		emit strokeChanged();
	}
}

QColor ColorSet::blank() const
{
	return m->blank;
}

void ColorSet::setBlank(QColor blank)
{
	if (m->blank != blank) {
		m->blank = blank;
		emit blankChanged();
	}
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
