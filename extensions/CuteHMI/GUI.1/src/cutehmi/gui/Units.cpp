#include "Units.hpp"

#include <cmath>

namespace cutehmi {
namespace gui {

constexpr qreal Units::INITIAL_QUADRAT;
constexpr qreal Units::INITIAL_STROKE_WIDTH_RATIO;
constexpr bool Units::INITIAL_ROUND_STROKE_WIDTH;

Units::Units(QObject * parent):
	QObject(parent),
	m(new Members{INITIAL_QUADRAT,
					INITIAL_QUADRAT / INITIAL_STROKE_WIDTH_RATIO,
					INITIAL_STROKE_WIDTH_RATIO,
					INITIAL_ROUND_STROKE_WIDTH, {}, {}})
{
	m->strokeWidthBindingConnection = connect(this, & Units::quadratChanged, this, & Units::strokeWidthBinding);
	m->strokeWidthRatioBindingConnection = connect(this, & Units::strokeWidthRatioChanged, this, & Units::strokeWidthBinding);
}

qreal Units::quadrat() const
{
	return m->quadrat;
}

void Units::setQuadrat(qreal quadrat)
{
	if (m->quadrat != quadrat) {
		m->quadrat = quadrat;
		emit quadratChanged();
	}
}

qreal Units::strokeWidth() const
{
	return m->strokeWidth;
}

void Units::setStrokeWidth(qreal strokeWidth)
{
	setStrokeWidth(strokeWidth, true);
}

qreal Units::strokeWidthRatio() const
{
	return m->strokeWidthRatio;
}

void Units::setStrokeWidthRatio(qreal ratio)
{
	if (m->strokeWidthRatio != ratio) {
		m->strokeWidthRatio = ratio;
		emit strokeWidthRatioChanged();
	}
}

bool Units::roundStrokeWidth() const
{
	return m->roundStrokeWidth;
}

void Units::setRoundStrokeWidth(bool roundStrokeWidth)
{
	if (m->roundStrokeWidth != roundStrokeWidth) {
		m->roundStrokeWidth = roundStrokeWidth;
		emit roundStrokeWidthChanged();
	}
}

void Units::strokeWidthBinding()
{
	setStrokeWidth(quadrat() / strokeWidthRatio(), false);
}

void Units::setStrokeWidth(qreal strokeWidth, bool breakBinding)
{
	if (breakBinding) {
		disconnect(m->strokeWidthBindingConnection);
		disconnect(m->strokeWidthRatioBindingConnection);
	}

	if (roundStrokeWidth())
		strokeWidth = std::max(std::round(strokeWidth), 1.0);

	if (m->strokeWidth != strokeWidth) {
		m->strokeWidth = strokeWidth;
		emit strokeWidthChanged();
	}
}

}
}

//(c)C: Copyright © 2020-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
