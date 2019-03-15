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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
