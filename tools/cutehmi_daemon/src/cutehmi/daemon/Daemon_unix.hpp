#ifndef DAEMON_UNIX_HPP
#define DAEMON_UNIX_HPP

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
		static int sigtermFd[2];
		static int sigUnhandledFd[2];

		_Daemon(const QString & pidFile);

		void initializeSignalHandling();

		void initializePidFile();

		void destroyPidFile();

	signals:
		void terminateRequested();

	private slots:
		void handleSigterm();

		void handleUnhandledSignals();

	private:
		int createPidFile();

		void lockPidFile();

		void writePidFile();

		void removePidFile();

	private:
		QString m_pidFile;
		int m_pidFd;
		std::unique_ptr<QSocketNotifier> m_sigtermSocketNotifier;
		std::unique_ptr<QSocketNotifier> m_unhandledSignalsSocketNotifier;
};


}
}

#endif // DAEMON_UNIX_HPP
