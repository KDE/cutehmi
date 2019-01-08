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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
