#include "../../../../include/cutehmi/modbus/internal/ServiceThread.hpp"
#include "../../../../include/cutehmi/modbus/Client.hpp"

namespace cutehmi {
namespace modbus {
namespace internal {

ServiceThread::ServiceThread(Client * client):
	m_run(0),
	m_sleep(0),
	m_client(client)
{
}

unsigned long ServiceThread::sleep() const
{
	return m_sleep;
}

void ServiceThread::setSleep(unsigned long sleep)
{
	m_sleep = sleep;
}

void ServiceThread::run()
{
	m_client->connect();
	if (m_client->isConnected())
		emit ran();
	else
		return;	// Do not enter the loop and don't trigger additional errors unnecessarily.

	while (m_run.loadAcquire()) {
		m_client->readAll(m_run);
		msleep(m_sleep);
	}
	m_client->disconnect();
}

void ServiceThread::start()
{
	m_run.storeRelease(1);
	Parent::start();
}

void ServiceThread::stop()
{
	m_run.storeRelease(0);
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
