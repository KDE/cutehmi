#include "Daemon.hpp"
#include "Daemon_unix.hpp"
#include "logging.hpp"
#include "../../../cutehmi.metadata.hpp"

#include <QCoreApplication>
#include <QDir>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

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

void sigHandler(int signal)
{
	// Reference implementation: http://doc.qt.io/qt-5/unix-signals.html.

	::write(_Daemon::signalFd[0], & signal, sizeof(signal));
}

int _Daemon::signalFd[2];

_Daemon::_Daemon(const QString & pidFile):
	m_pidFile(pidFile)
{
}

void _Daemon::initializeSignalHandling()
{
	// Reference implementation: http://doc.qt.io/qt-5/unix-signals.html.

	if (::socketpair(AF_UNIX, SOCK_STREAM, 0, signalFd))
		CUTEHMI_DIE("Could not create socket pair for signal handling.");
	m_signalSocketNotifier.reset(new QSocketNotifier(signalFd[1], QSocketNotifier::Read));
	connect(m_signalSocketNotifier.get(), & QSocketNotifier::activated, this, & _Daemon::handleSignal);

}

void _Daemon::initializePidFile()
{
	m_pidFd = createPidFile();
	lockPidFile();
	writePidFile();
}

void _Daemon::destroyPidFile()
{
	removePidFile();
}

void _Daemon::handleSignal()
{
	// Reference implementation: http://doc.qt.io/qt-5/unix-signals.html.

	m_signalSocketNotifier->setEnabled(false);

	int signal;
	::read(signalFd[1], & signal, sizeof(signal));

	switch (signal) {
		case SIGTERM:
			CUTEHMI_INFO("Termination requested by SIGTERM (" << signal << ") signal.");
			emit exitRequested(EXIT_SUCCESS);
			break;
		case SIGINT:
			CUTEHMI_INFO("Interrupt requested by SIGINT (" << signal << ") signal.");
			emit exitRequested(128 + signal);
			break;
		case SIGHUP:
			CUTEHMI_INFO("Restarting due to SIGHUP (" << signal << ") signal.");
			emit exitRequested(Daemon::EXIT_AGAIN);
			break;
		case SIGQUIT:
			CUTEHMI_DIE("Aborting due to SIGQUIT (%d) signal.", signal);
		default:
			CUTEHMI_WARNING("Captured unhandled signal (" << signal << ").");
	}

	m_signalSocketNotifier->setEnabled(true);
}

int _Daemon::createPidFile()
{
	int fd = open(m_pidFile.toLocal8Bit().constData(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		CUTEHMI_DIE("Could not open PID file '%s'; %s.", m_pidFile.toLocal8Bit().constData(), strerror(errno));

	// Set close-on-exec flag.
	int flags = fcntl(fd, F_GETFD);
	if (flags == -1)
		CUTEHMI_DIE("Could not access flags of PID file '%s'; %s.", m_pidFile.toLocal8Bit().constData(), strerror(errno));
	flags |= FD_CLOEXEC;
	if (fcntl(fd, F_SETFD, flags) == -1)
		CUTEHMI_DIE("Could not update flags of PID file '%s'; %s.", m_pidFile.toLocal8Bit().constData(), strerror(errno));

	return fd;
}

void _Daemon::lockPidFile()
{
	struct flock fl;

	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;

	if (fcntl(m_pidFd, F_SETLK, & fl) == -1) {
		if (errno  == EAGAIN || errno == EACCES)
			CUTEHMI_DIE("PID file '%s' is already locked by another process. Ensure that another instance of '" CUTEHMI_DAEMON_NAME "' with the same 'pidfile' option is not already running.", m_pidFile.toLocal8Bit().constData());
		else
			CUTEHMI_DIE("Unable to lock PID file '%s'; %s.", m_pidFile.toLocal8Bit().constData(), strerror(errno));
	}
}

void _Daemon::writePidFile()
{
	if (ftruncate(m_pidFd, 0) == -1)
		CUTEHMI_DIE("Could not truncate PID file '%s'.", m_pidFile.toLocal8Bit().constData());

	QByteArray buff = QByteArray::number(getpid());
	if (static_cast<int>(write(m_pidFd, buff.constData(), static_cast<std::size_t>(buff.size()))) != buff.size())
		CUTEHMI_DIE("Could not store PID in the PID file '%s'.", m_pidFile.toLocal8Bit().constData());
}

void _Daemon::removePidFile()
{
	if (close(m_pidFd) == -1)
		CUTEHMI_DIE("Could not close descriptor of the PID file '%s'; %s.", m_pidFile.toLocal8Bit().constData(), strerror(errno));

	if (unlink(m_pidFile.toLocal8Bit().constData()) == -1)
		CUTEHMI_WARNING("Could not remove PID file '" << m_pidFile << "'; " << strerror(errno) << ".");
}


void Daemon::_init()
{
	//<cutehmi.daemon.1-silent_initialization.principle>

	// Configure logging.
	openlog(CUTEHMI_DAEMON_NAME, LOG_PID | LOG_NDELAY, LOG_USER);
	qInstallMessageHandler(::syslogMessageHandler);

	// As logging has been configured daemon can use logging macros. Standard file descriptors still have to be closed.
	CUTEHMI_INFO("Starting " << CUTEHMI_DAEMON_NAME << "...");

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

	//</cutehmi.daemon.1-silent_initialization.principle>

	// Create helper class.
	QString pidFilePath = data()->cmd->value(data()->opt->pidfile);
	if (QDir::isRelativePath(data()->cmd->value(data()->opt->pidfile)))
		pidFilePath.prepend(QDir(data()->cmd->value(data()->opt->basedir)).absolutePath() + "/");
	_daemon = new _Daemon(pidFilePath);

	// Create exit point through 'terminateRequested' signal.
	QObject::connect(_daemon, & _Daemon::exitRequested, [](int exitCode) {
		QCoreApplication::exit(exitCode);
	});

	// Initialize signal handling.
	_daemon->initializeSignalHandling();

	// Initialize PID file.
	_daemon->initializePidFile();

	// Install signal handler.
	struct sigaction sigAct;
	sigAct.sa_handler = sigHandler;
	sigemptyset(& sigAct.sa_mask);
	sigAct.sa_flags = 0;
	sigaction(SIGTERM, & sigAct, nullptr);
	sigaction(SIGINT, & sigAct, nullptr);
	sigaction(SIGQUIT, & sigAct, nullptr);
	sigaction(SIGHUP, & sigAct, nullptr);

	// Execute core.
	exec();
}

void Daemon::_exec()
{
}

void Daemon::_destroy()
{
	CUTEHMI_INFO("Daemon finished execution with exit code '" << exitCode() << "'.");

	_daemon->destroyPidFile();
	_daemon->deleteLater();

	closelog();	// "The use of closelog() is optional." -- SYSLOG(3).
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
