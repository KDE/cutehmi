#include "Service.hpp"
#include "Client.hpp"
#include "CommunicationThread.hpp"

namespace cutehmi {
namespace stupid {

Service::Service(Client * client):
	m_thread(new CommunicationThread(client)),
	m_client(client)
{
}

Service::~Service()
{
	if (m_thread->isRunning())
		stop();
}

unsigned long Service::sleep() const
{
	return m_thread->sleep();
}

void Service::setSleep(unsigned long sleep)
{
	m_thread->setSleep(sleep);
}

void Service::init()
{
	m_client->init();
}

void Service::start()
{
	m_client->connect();
	qDebug("Starting STUPiD client thread...");
	m_thread->start();
}

void Service::stop()
{
	qDebug("Stopping STUPiD client thread...");
	m_thread->stop();
	m_thread->quit();
	m_thread->wait();
	qDebug("STUPiD client thread finished.");
	m_client->disconnect();
}

}
}
