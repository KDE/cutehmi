#include "CommunicationThread.hpp"
#include "Client.hpp"

namespace cutehmi {
namespace modbus {

CommunicationThread::CommunicationThread(Client * client):
	m_client(client)
{
}

void CommunicationThread::run()
{
	m_client->readAll();	// @todo synchronization
	sleep(5);	// @todo temp hard coded.
}

}
}
