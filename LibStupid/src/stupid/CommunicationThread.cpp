#include "CommunicationThread.hpp"
#include "Client.hpp"

namespace cutehmi {
namespace stupid {

CommunicationThread::CommunicationThread(Client * client):
	m_run(0),
	m_sleep(0),
	m_client(client)
{
}

unsigned long CommunicationThread::sleep() const
{
	return m_sleep;
}

void CommunicationThread::setSleep(unsigned long sleep)
{
	m_sleep = sleep;
}

void CommunicationThread::run()
{
	while (m_run.load()) {
		m_client->readAll(m_run);	// Note: Because of relaxed model readAll() may theoretically skip first reads by calling readAll(0).
		msleep(m_sleep);
	}
}

void CommunicationThread::start()
{
	m_run.store(1);
	Parent::start();
}

void CommunicationThread::stop()
{
	m_run.store(0);
}


}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
