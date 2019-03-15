#include <cutehmi/gpio/internal/LineEventMonitorThread.hpp>

namespace cutehmi {
namespace gpio {
namespace internal {

LineEventMonitorThread::LineEventMonitorThread(QObject * parent):
	QThread(parent),
	m(new Members)
{
	Register_gpiod_line_event();
}

void LineEventMonitorThread::setLine(gpiod_line * line)
{
	m->line = line;
}

void LineEventMonitorThread::run()
{
	while (1) {
		if (QThread::currentThread()->isInterruptionRequested())
			break;
		int waitResult = gpiod_line_event_wait(m->line, & m->timeout);
		if (waitResult == 1) {
			gpiod_line_event event;
			if (gpiod_line_event_read(m->line, & event) == 0)
				emit eventDetected(event);
			else
				CUTEHMI_WARNING("An error occured while reading line event.");
		} else if (waitResult == -1)
			CUTEHMI_WARNING("An error occured while waiting for line event.");
	}
}

int LineEventMonitorThread::Register_gpiod_line_event()
{
	static int id = qRegisterMetaType<gpiod_line_event>();
	return id;
}

}
}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
