#include "CommunicationThread.hpp"
#include "Client.hpp"

namespace cutehmi {
namespace modbus {

CommunicationThread::CommunicationThread(Client * client):
	m_run(false),
	m_client(client)
{
}

void CommunicationThread::run()
{
	while (m_run) {
		m_client->readAll();	// @todo synchronization
		sleep(5);	// @todo temp hard coded.
	}
}


void CommunicationThread::start()
{
	m_run = true;
	Parent::start();
}

void CommunicationThread::stop()
{
	m_run = false;
}


}
}
