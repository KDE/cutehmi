#ifndef H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_DAEMON_u_UNIX_HPP
#define H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_DAEMON_u_UNIX_HPP

#include <QObject>
#include <QSocketNotifier>

#include <memory>

namespace cutehmi {
namespace daemon {

class Daemon;

/**
 * Unix-specific daemon helper.
 */
class _Daemon:
	public QObject
{
	Q_OBJECT

	public:
		static int signalFd[2];

		_Daemon(const QString & pidFile);

		void initializeSignalHandling();

		void initializePidFile();

		void destroyPidFile();

	signals:
		void exitRequested(int exitCode);

	private slots:
		void handleSignal();

	private:
		int createPidFile();

		void lockPidFile();

		void writePidFile();

		void removePidFile();

	private:
		QString m_pidFile;
		int m_pidFd;
		std::unique_ptr<QSocketNotifier> m_signalSocketNotifier;
		std::unique_ptr<QSocketNotifier> m_unhandledSignalsSocketNotifier;
};


}
}

#endif
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
