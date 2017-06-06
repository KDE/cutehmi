#include "../../include/modbus/Service.hpp"
#include "../../include/modbus/Client.hpp"

#include <base/Prompt.hpp>

namespace cutehmi {
namespace modbus {

Service::Service(const QString & name, Client * client, QObject * parent):
	services::Service(name, parent),
	m(new Members(client))
{
	QObject::connect(m->client, & Client::error, this, & Service::handleError);
	QObject::connect(m->client, & Client::connected, this, & Service::onClientConnected);
	QObject::connect(m->client, & Client::disconnected, this, & Service::onClientDisconnected);
}

Service::~Service()
{
	if (state() != STOPPED)
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
	setState(STARTING);
	CUTEHMI_MODBUS_QDEBUG("Starting Modbus client thread...");
	m->thread->start();
	return state();
}

Service::state_t Service::customStop()
{
	setState(STOPPING);
	CUTEHMI_MODBUS_QDEBUG("Stopping Modbus client thread...");
	m->thread->stop();
	m->thread->quit();
	m->thread->wait();
	CUTEHMI_MODBUS_QDEBUG("Modbus client thread finished.");
	if (!m->client->isConnected())
		setState(STOPPED);
	return state();
}

void Service::onClientConnected()
{
	CUTEHMI_MODBUS_QDEBUG("Modbus client connected.");
	setState(STARTED);
}

void Service::onClientDisconnected()
{
	CUTEHMI_MODBUS_QDEBUG("Modbus client disconnected.");
	setState(STOPPED);
}

void Service::handleError(cutehmi::base::ErrorInfo errorInfo)
{
	base::Prompt::Critical(errorInfo);
	stop();
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
