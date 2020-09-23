#ifndef H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_LINE_HPP
#define H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_LINE_HPP

#include "internal/common.hpp"
#include "LineConfig.hpp"
#include "internal/LineEventMonitorThread.hpp"

#include <gpiod.h>

#include <QObject>

namespace cutehmi {
namespace gpio {

class CUTEHMI_GPIO_API Line:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
		Q_PROPERTY(QString name READ name)
		Q_PROPERTY(cutehmi::gpio::LineConfig * config READ config WRITE setConfig NOTIFY configChanged)
		Q_PROPERTY(bool used READ used NOTIFY usedChanged)
		Q_PROPERTY(QString consumer READ consumer WRITE setConsumer NOTIFY consumerChanged)

		explicit Line(gpiod_line * line, QObject * parent = nullptr);

		~Line() override;

		int value() const;

		void setValue(int value);

		QString name() const;

		LineConfig * config() const;

		void setConfig(LineConfig * config);

		QString consumer() const;

		void setConsumer(const QString & consumer);

		bool used() const;

	signals:
		void valueChanged();

		void configChanged();

		void consumerChanged();

		void usedChanged();

	private slots:
		void requestLine();

		void releaseLine();

		void requestValue();

		void handleLineEvent(gpiod_line_event event);

	private:
		void readLineInfo();

		struct Members
		{
			gpiod_line * line;
			int value;
			QString name;
			LineConfig * config;
			gpiod_line_request_config requestConfig;
			QByteArray consumer;
			bool used;
			internal::LineEventMonitorThread monitorThread;

			Members(gpiod_line * p_line):
				line(p_line),
				value(0),
				config(nullptr),
				used(false)
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
