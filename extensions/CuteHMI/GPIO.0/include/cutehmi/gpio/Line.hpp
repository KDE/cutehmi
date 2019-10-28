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

//(c)C: Copyright © 2019, CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
