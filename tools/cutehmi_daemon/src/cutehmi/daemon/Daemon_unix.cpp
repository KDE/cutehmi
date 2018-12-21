#include "Daemon.hpp"
#include "Daemon_unix.hpp"
#include "logging.hpp"
#include "../../../cutehmi.metadata.hpp"

#include <QCoreApplication>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
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

static volatile sig_atomic_t sigCaptured = 0;

void sigHandler(int signal)
{
	// Reference implementation: http://doc.qt.io/qt-5/unix-signals.html.

	sigCaptured = signal;

	if (signal == SIGTERM)
		::write(_Daemon::sigtermFd[0], & signal, sizeof(signal));
	else
		::write(_Daemon::sigUnhandledFd[0], & signal, sizeof(signal));
}

int _Daemon::sigtermFd[2];
int _Daemon::sigUnhandledFd[2];

void _Daemon::initializeSignalHandling()
{
	// Reference implementation: http://doc.qt.io/qt-5/unix-signals.html.

	if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigtermFd))
	   CUTEHMI_DIE("Could not create socket pair for SIGTERM signal.");
	m_sigtermSocketNotifier.reset(new QSocketNotifier(sigtermFd[1], QSocketNotifier::Read));
	connect(m_sigtermSocketNotifier.get(), & QSocketNotifier::activated, this, & _Daemon::handleSigterm);

	if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigUnhandledFd))
	   CUTEHMI_DIE("Could not create socket pair for detection of unhandled signals.");
	m_unhandledSignalsSocketNotifier.reset(new QSocketNotifier(sigUnhandledFd[1], QSocketNotifier::Read));
	connect(m_unhandledSignalsSocketNotifier.get(), & QSocketNotifier::activated, this, & _Daemon::handleUnhandledSignals);
}

void _Daemon::handleSigterm()
{
	// Reference implementation: http://doc.qt.io/qt-5/unix-signals.html.

	m_sigtermSocketNotifier->setEnabled(false);

	int signal;
	::read(sigtermFd[1], & signal, sizeof(signal));

	CUTEHMI_INFO("Termination requested by SIGTERM (" << signal << ") signal.");

	emit terminateRequested();

	m_sigtermSocketNotifier->setEnabled(true);
}

void _Daemon::handleUnhandledSignals()
{
	// Reference implementation: http://doc.qt.io/qt-5/unix-signals.html.

	m_unhandledSignalsSocketNotifier->setEnabled(false);

	int signal;
	::read(sigUnhandledFd[1], & signal, sizeof(signal));

	CUTEHMI_WARNING("Captured unhandled signal (" << signal << ").");

	m_unhandledSignalsSocketNotifier->setEnabled(true);
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
		CUTEHMI_DIE("Failed to change working directory to '/'.");

	// Close file descriptors.
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// Create helper class.
	_daemon = new _Daemon;

	// Create exit point through 'terminateRequested' signal.
	if (data()->app)
		QObject::connect(_daemon, & _Daemon::terminateRequested, data()->app, & QCoreApplication::quit);
	else
		CUTEHMI_DIE("Could not obtain instance of QCoreApplication.");

	// Initialize signal handling.
	_daemon->initializeSignalHandling();

	// Install signal handler.
	struct sigaction sigAct;
	sigAct.sa_handler = sigHandler;
	sigemptyset(& sigAct.sa_mask);
	sigAct.sa_flags = 0;
	sigaction(SIGTERM, & sigAct, NULL);

	// Execute core.
	exec();
}

void Daemon::_exec()
{
}

void Daemon::_destroy()
{
	CUTEHMI_INFO("Daemon finished execution with exit code '" << exitCode() << "'.");

	_daemon->deleteLater();
	closelog();	// "The use of closelog() is optional." -- SYSLOG(3).
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
