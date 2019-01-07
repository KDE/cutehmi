#ifndef LINEEVENTMONITORTHREAD_HPP
#define LINEEVENTMONITORTHREAD_HPP

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


#endif // LINEEVENTMONITORTHREAD_HPP
