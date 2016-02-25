#include "ClientRunner.hpp"
#include "Client.hpp"

namespace cutehmi {
namespace modbus {

ClientRunner::ClientRunner(Client * client):
	m_thread(new CommunicationThread(client)),
	m_client(client)
{
}

ClientRunner::~ClientRunner()
{
	if (m_thread->isRunning())
		stop();
}

void ClientRunner::start()
{
	m_client->connect();
	qDebug("Starting client thread...");
	m_thread->start();
}

void ClientRunner::stop()
{
	qDebug("Stopping client thread...");
	m_thread->stop();
	m_thread->quit();
	m_thread->wait();
	qDebug("Client thread finished.");
	m_client->disconnect();
}

}
}
