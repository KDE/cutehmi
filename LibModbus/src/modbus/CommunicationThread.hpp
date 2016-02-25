#ifndef COMMUNICATIONTHREAD_H
#define COMMUNICATIONTHREAD_H

#include <QThread>

namespace cutehmi {
namespace modbus {

class Client;

class CommunicationThread:
	public QThread
{
	Q_OBJECT
	typedef QThread Parent;

	public:
		explicit CommunicationThread(Client * client);

	public:
		void run() override;

	public slots:
		void start();

		void stop();

	private:
		bool m_run;
		Client * m_client;
};

}
}

#endif // COMMUNICATIONTHREAD_H
