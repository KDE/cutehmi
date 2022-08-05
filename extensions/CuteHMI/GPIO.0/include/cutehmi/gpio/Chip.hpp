#ifndef H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_CHIP_HPP
#define H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_CHIP_HPP

#include "internal/common.hpp"
#include "Line.hpp"

#include <gpiod.h>

#include <QObject>
#include <QQmlListProperty>
#include <QVector>
#include <QQmlEngine>

namespace cutehmi {
namespace gpio {

class CUTEHMI_GPIO_API Chip:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(Chip)

	public:
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString label READ label NOTIFY labelChanged)
		Q_PROPERTY(QQmlListProperty<cutehmi::gpio::Line> lines READ lines NOTIFY linesChanged)

		explicit Chip(QObject * parent = nullptr);

		~Chip() override;

		QString name() const;

		void setName(const QString & name);

		QString label() const;

		const QQmlListProperty<Line> lines();

	public slots:
		void open();

		void close();

	signals:
		void nameChanged();

		void labelChanged();

		void linesChanged();

	private:
		typedef QVector<Line *> LinesDataContainer;

		static int LineCount(QQmlListProperty<Line> * property);

		static Line * LineAt(QQmlListProperty<Line> * property, int index);

		void setLabel(const QString & label);

		void resetLineData(int lineCount);

		void updateProperties();

		void clearProperties();

		struct Members
		{
			gpiod_chip * chip;
			QString name;
			QString label;
			LinesDataContainer linesData;
			QQmlListProperty<Line> lines;

			Members(Chip * p_parent):
				chip(nullptr),
				lines(p_parent, & linesData, & Chip::LineCount, & Chip::LineAt)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
