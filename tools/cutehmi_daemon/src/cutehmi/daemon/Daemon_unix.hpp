#ifndef H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_DAEMON_u_UNIX_HPP
#define H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_DAEMON_u_UNIX_HPP

#include <QObject>
#include <QSocketNotifier>

#include <memory>

namespace cutehmi {
namespace daemon {

/**
 * Unix-specific daemon helper.
 */
class _Daemon:
	public QObject
{
	Q_OBJECT

	public:
		static int sigtermFd[2];
		static int sigUnhandledFd[2];

		void initializeSignalHandling();

	signals:
		void terminateRequested();

	private slots:
		void handleSigterm();

		void handleUnhandledSignals();

	private:
		std::unique_ptr<QSocketNotifier> m_sigtermSocketNotifier;
		std::unique_ptr<QSocketNotifier> m_unhandledSignalsSocketNotifier;
};


}
}

#endif
