#include "../../../../include/cutehmi/stupid/internal/CommunicationThread.hpp"
#include "../../../../include/cutehmi/stupid/Client.hpp"

namespace cutehmi {
namespace stupid {
namespace internal {

CommunicationThread::CommunicationThread(Client * client):
	m(new Members{0, 0, client})
{
}

unsigned long CommunicationThread::sleep() const
{
	return m->sleep;
}

void CommunicationThread::setSleep(unsigned long sleep)
{
	m->sleep = sleep;
}

void CommunicationThread::run()
{
	while (m->run.loadAcquire()) {
		m->client->checkDatabaseConnectionStatus();
		m->client->readAll(m->run);
		msleep(m->sleep);
	}
}

void CommunicationThread::start()
{
	m->run.storeRelease(1);
	Parent::start();
}

void CommunicationThread::stop()
{
	m->run.storeRelease(0);
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
