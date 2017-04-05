#include "../../include/modbus/Service.hpp"
#include "../../include/modbus/Client.hpp"

namespace cutehmi {
namespace modbus {

Service::Service(const QString & name, Client * client, QObject * parent):
	services::Service(name, parent),
	m(new Members(client))
{
}

Service::~Service()
{
	if (m->thread->isRunning())
		stop();
}

unsigned long Service::sleep() const
{
	return m->thread->sleep();
}

void Service::setSleep(unsigned long sleep)
{
	m->thread->setSleep(sleep);
}

Service::state_t Service::customStart()
{
	m->client->connect();
	CUTEHMI_MODBUS_QDEBUG("Starting Modbus client thread...");
	m->thread->start();
	return STARTED;
}

Service::state_t Service::customStop()
{
	CUTEHMI_MODBUS_QDEBUG("Stopping Modbus client thread...");
	m->thread->stop();
	m->thread->quit();
	m->thread->wait();
	CUTEHMI_MODBUS_QDEBUG("Modbus client thread finished.");
	m->client->disconnect();
	return STOPPED;
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
