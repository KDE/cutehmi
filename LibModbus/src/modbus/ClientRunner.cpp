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

unsigned long ClientRunner::sleep() const
{
	return m_thread->sleep();
}

void ClientRunner::setSleep(unsigned long sleep)
{
	m_thread->setSleep(sleep);
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

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
