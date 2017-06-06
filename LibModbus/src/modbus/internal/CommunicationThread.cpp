#include "../../../include/modbus/internal/CommunicationThread.hpp"
#include "../../../include/modbus/Client.hpp"

namespace cutehmi {
namespace modbus {
namespace internal {

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
	m_client->connect();
	while (m_run.load()) {
		//@todo check connection status.
		m_client->readAll(m_run);
		msleep(m_sleep);
	}
	m_client->disconnect();
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
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
