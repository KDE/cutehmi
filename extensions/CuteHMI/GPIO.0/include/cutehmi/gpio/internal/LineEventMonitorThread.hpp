#ifndef H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_INTERNAL_LINEEVENTMONITORTHREAD_HPP
#define H_EXTENSIONS_CUTEHMI_GPIO_0_INCLUDE_CUTEHMI_GPIO_INTERNAL_LINEEVENTMONITORTHREAD_HPP

#include "common.hpp"

#include <gpiod.h>

#include <QThread>

namespace cutehmi {
namespace gpio {
namespace internal {

// One thread per Linie isn't the most efficient approach, but let's stick to Donald Knuth's wisdom that "premature optimization is
// the root of all evil".
class CUTEHMI_GPIO_PRIVATE LineEventMonitorThread:
	public QThread
{
	Q_OBJECT

	public:
		LineEventMonitorThread(QObject * parent = nullptr);

		void setLine(gpiod_line * line);

		void run() override;

	signals:
		void eventDetected(gpiod_line_event event);

	private:
		static int Register_gpiod_line_event();

		struct Members
		{
			gpiod_line * line = nullptr;
			timespec timeout = {1, 0};
		};

		MPtr<Members> m;
};

}
}
}

Q_DECLARE_METATYPE(gpiod_line_event)


#endif

//(c)C: Copyright © 2019, CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
