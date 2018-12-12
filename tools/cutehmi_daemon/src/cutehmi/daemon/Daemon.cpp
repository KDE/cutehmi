#include "Daemon.hpp"
#include "../../../cutehmi.metadata.hpp"
//#include "Settings.hpp"
//#include "Core.hpp"

#include <syslog.h>

#include <thread>
#include <chrono>

namespace cutehmi {
namespace daemon {

//constexpr int Daemon::SLEEP_UNIT;

Daemon::Daemon():
	m_terminate(false)
{
	// Configure logging.
	openlog(CUTEHMI_DAEMON_NAME, LOG_PID | LOG_NDELAY, LOG_USER);
	qInstallMessageHandler(& Daemon::MessageHandler);

	_init();
}

Daemon::~Daemon()
{
	closelog();	// "The use of closelog() is optional." -- SYSLOG(3).
}

void Daemon::terminate()
{
	m_terminate = true;
}

//void Daemon::exec(int maxFails)
//{
//}

void Daemon::MessageHandler(QtMsgType type, const QMessageLogContext & context, const QString & msg)
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
}
