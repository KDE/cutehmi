#include "internal/LineEventMonitorThread.hpp"

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
				CUTEHMI_WARNING("An error occurred while reading line event.");
		} else if (waitResult == -1)
			CUTEHMI_WARNING("An error occurred while waiting for line event.");
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

//(c)C: Copyright © 2019-2023, Michał Policht <michal@policht.pl>, Yuri Chornoivan <yurchor@ukr.net>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
