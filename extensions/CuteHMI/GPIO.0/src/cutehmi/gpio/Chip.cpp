#include "Chip.hpp"

namespace cutehmi {
namespace gpio {

Chip::Chip(QObject * parent):
	QObject(parent),
	m(new Members(this))
{
	connect(this, & Chip::nameChanged, this, & Chip::open);
}

Chip::~Chip()
{
	close();
}

QString Chip::name() const
{
	return m->name;
}

void Chip::setName(const QString & name)
{
	if (m->name != name) {
		m->name = name;
		emit nameChanged();
	}
}

QString Chip::label() const
{
	return m->label;
}

const QQmlListProperty<Line> Chip::lines()
{
	return m->lines;
}

void Chip::open()
{
	close();
	m->chip = gpiod_chip_open_by_name(m->name.toLocal8Bit().constData());
	if (m->chip != nullptr)
		updateProperties();
	else
		CUTEHMI_WARNING("Could not open GPIO chip '" << m->name << "'.");
}

void Chip::close()
{
	clearProperties();
	if (m->chip) {
		gpiod_chip_close(m->chip);
		m->chip = nullptr;
	}
}

qsizetype Chip::LineCount(QQmlListProperty<Line> * property)
{
	return static_cast<LinesDataContainer *>(property->data)->count();
}

Line * Chip::LineAt(QQmlListProperty<Line> * property, qsizetype index)
{
	Chip * chip = static_cast<Chip *>(property->object);
	LinesDataContainer * linesData = static_cast<LinesDataContainer *>(property->data);
	if (!linesData->at(index))
		linesData->replace(index, new Line(gpiod_chip_get_line(chip->m->chip, static_cast<unsigned int>(index))));
	return linesData->at(index);
}

void Chip::setLabel(const QString & label)
{
	if (m->label != label) {
		m->label = label;
		emit labelChanged();
	}
}

void Chip::resetLineData(int lineCount)
{
	if (m->linesData.count() != lineCount) {
		for (LinesDataContainer::iterator it = m->linesData.begin(); it != m->linesData.end(); ++it)
			if (*it)
				(*it)->deleteLater();
		m->linesData.fill(nullptr, lineCount);
		emit linesChanged();
	}
}

void Chip::updateProperties()
{
	setLabel(gpiod_chip_label(m->chip));
	resetLineData(static_cast<int>(gpiod_chip_num_lines(m->chip)));
}

void Chip::clearProperties()
{
	setLabel(QString());
	resetLineData(0);
}

}
}

//(c)C: Copyright © 2019-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
