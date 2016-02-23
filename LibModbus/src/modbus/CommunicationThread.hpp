#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_COMMUNICATIONTHREAD_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_COMMUNICATIONTHREAD_HPP

#include <QThread>

namespace cutehmi {
namespace modbus {

class Client;

class CommunicationThread:
	public QThread
{
	Q_OBJECT

	public:
		CommunicationThread(Client * client);

	public:
		void run() override;

	private:
		Client * m_client;
};

}
}

#endif
