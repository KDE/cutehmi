#include "Daemon.hpp"
#include "logging.hpp"
#include "../../../cutehmi.metadata.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>

namespace {

	void syslogMessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg)
	{
		QByteArray localMsg = msg.toLocal8Bit();
		switch (type) {
	#ifndef CUTEHMI_NDEBUG
			case QtDebugMsg:
				syslog(LOG_DEBUG, "%s: %s [%s:%u, %s]", context.category, localMsg.constData(), context.file, context.line, context.function);
				break;
			case QtInfoMsg:
				syslog(LOG_INFO, "%s: %s [%s:%u, %s]", context.category, localMsg.constData(), context.file, context.line, context.function);
				break;
			case QtWarningMsg:
				syslog(LOG_WARNING, "%s: %s [%s:%u, %s]", context.category, localMsg.constData(), context.file, context.line, context.function);
				break;
			case QtCriticalMsg:
				syslog(LOG_CRIT, "%s: %s [%s:%u, %s]", context.category, localMsg.constData(), context.file, context.line, context.function);
				break;
			case QtFatalMsg:
				syslog(LOG_ALERT, "%s: %s [%s:%u, %s]", context.category, localMsg.constData(), context.file, context.line, context.function);
				break;
	#else
			case QtDebugMsg:
				syslog(LOG_DEBUG, "%s: %s", context.category, localMsg.constData());
				break;
			case QtInfoMsg:
				syslog(LOG_INFO, "%s: %s", context.category, localMsg.constData());
				break;
			case QtWarningMsg:
				syslog(LOG_WARNING, "%s: %s", context.category, localMsg.constData());
				break;
			case QtCriticalMsg:
				syslog(LOG_CRIT, "%s: %s", context.category, localMsg.constData());
				break;
			case QtFatalMsg:
				syslog(LOG_ALERT, "%s: %s", context.category, localMsg.constData());
				break;
	#endif
		}
	}
}

namespace cutehmi {
namespace daemon {

static volatile sig_atomic_t sigHandled = 0;

void sigHandler(int signal)
{
	if (signal == SIGTERM) {
		CUTEHMI_INFO("Termination requested by SIGTERM signal.");
		sigHandled = signal;
	} else
		CUTEHMI_WARNING("Captured unhandled signal (" << signal << ").");
}

void Daemon::_init()
{
	// Configure logging.
	openlog(CUTEHMI_DAEMON_NAME, LOG_PID | LOG_NDELAY, LOG_USER);
	qInstallMessageHandler(::syslogMessageHandler);

	pid_t pid, sid;

	// Detach from controlling tty (tty is given per session).
	// Note: when using std::exit() stack unwinding is not performed, which means destructors won't be called.

	// Fork and exit parent process to become a session leader.
	pid = fork();
	if (pid < 0) {
		CUTEHMI_WARNING("Daemon could not fork.");
		std::exit(EXIT_FAILURE);
	} else if (pid > 0)
		std::exit(EXIT_SUCCESS);	// tty session leader quits.

	// Now process may become a session leader and detach from parent session.
	sid = setsid();
	if (sid < 0)
		CUTEHMI_DIE("Failed to initialize daemon (could not create session).");

	// Second fork to become orphan and ensure that process will not acquire tty (see daemon(3)).
	pid = fork();
	if (pid < 0) {
		CUTEHMI_WARNING("Daemon could not fork.");
		std::exit(EXIT_FAILURE);
	} else if (pid > 0)
		std::exit(EXIT_SUCCESS); // Session leader quits.

	// Orphaned daemon process continues...

	umask(0);

	// This is mainly to avoid locking former working directory.
	if ((chdir("/")) < 0)
		CUTEHMI_DIE("Failed to change working directory.");

	// Close file descriptors.
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// Install signal handler.
	struct sigaction sigAct;
	sigAct.sa_handler = sigHandler;
	sigemptyset(& sigAct.sa_mask);
	sigAct.sa_flags = 0;
	sigaction(SIGTERM, & sigAct, NULL);
}

void Daemon::_destroy()
{
	closelog();	// "The use of closelog() is optional." -- SYSLOG(3).
}

void Daemon::_watch()
{
	if (sigHandled)
		terminate();
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
