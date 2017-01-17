#include "Service.hpp"
#include "Client.hpp"
#include "CommunicationThread.hpp"

namespace cutehmi {
namespace stupid {

Service::Service(const QString & name, Client * client, QObject * parent):
	base::Service(name, parent),
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

Service::state_t Service::customStart()
{
	m_client->connect();
	qDebug("Starting STUPiD client thread...");
	m_thread->start();
	return STARTED;
}

Service::state_t Service::customStop()
{
	qDebug("Stopping STUPiD client thread...");
	m_thread->stop();
	m_thread->quit();
	m_thread->wait();
	qDebug("STUPiD client thread finished.");
	m_client->disconnect();
	return STOPPED;
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
