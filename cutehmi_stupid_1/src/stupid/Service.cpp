#include "../../include/stupid/Service.hpp"
#include "../../include/stupid/Client.hpp"
#include "../../include/stupid/internal/CommunicationThread.hpp"

#include <base/Prompt.hpp>

namespace cutehmi {
namespace stupid {

Service::Service(const QString & name, Client * client, QObject * parent):
	services::Service(name, parent),
	m(new Members{std::unique_ptr<internal::CommunicationThread>(new internal::CommunicationThread(client)), client})
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
	m->client->connect();	// onClientConnected() is connected to m->client->connected() signal.
	return state();
}

Service::state_t Service::customStop()
{
	if (m->thread->isRunning()) {
		CUTEHMI_UTILS_DEBUG("Stopping STUPiD client thread...");
		m->thread->stop();
		m->thread->quit();
		m->thread->wait();
		CUTEHMI_UTILS_DEBUG("STUPiD client thread finished.");
	}
	setState(STOPPING);
	m->client->disconnect();
	return state();
}

void Service::onClientConnected()
{
	CUTEHMI_UTILS_DEBUG("Starting STUPiD client thread...");
	m->thread->start();
	setState(STARTED);
}

void Service::onClientDisconnected()
{
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
