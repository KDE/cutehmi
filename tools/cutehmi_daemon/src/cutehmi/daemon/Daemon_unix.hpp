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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
