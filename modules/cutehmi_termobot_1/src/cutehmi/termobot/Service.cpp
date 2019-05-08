#include "Service.hpp"

#include <cutehmi/Prompt.hpp>

namespace cutehmi {
namespace termobot {

Service::Service(const QString & name, DatabaseThread * databaseThread, QObject * parent):
	services::Service(name, parent),
	m(new Members{databaseThread})
{
	QObject::connect(m->databaseThread, &DatabaseThread::connected, this, &Service::databaseConnected);
	QObject::connect(m->databaseThread, &DatabaseThread::error, this, &Service::databaseError);
}

Service::State Service::customStart()
{
	setState(STARTING);
	m->databaseThread->start();
	return state();
}

Service::~Service()
{
	if (state() != STOPPED)
		stop();
}

void Service::databaseConnected()
{
	setState(STARTED);
}

void Service::databaseError(ErrorInfo errInfo)
{
	Prompt::Critical(errInfo);
	stop();
}

Service::State Service::customStop()
{
	setState(STOPPING);
	if (m->databaseThread->isRunning()) {
		CUTEHMI_LOG_DEBUG("Stopping Termobot DatabaseThread...");
		m->databaseThread->quit();
		m->databaseThread->wait();
		CUTEHMI_LOG_DEBUG("Termobot DatabaseThread finished.");
	}
	return STOPPED;
}

} // namespace termobot
} // namespace cutehmi

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
