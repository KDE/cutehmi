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

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
