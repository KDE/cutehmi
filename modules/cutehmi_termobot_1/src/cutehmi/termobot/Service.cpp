#include "Service.hpp"

namespace cutehmi {
namespace termobot {

Service::Service(const QString & name, DatabaseThread * databaseThread, QObject * parent):
	services::Service(name, parent),
	m(new Members{databaseThread})
{}

Service::State Service::customStart()
{
	m->databaseThread->start();
    return STARTED;
}

Service::~Service()
{
	if (state() != STOPPED)
		stop();
}

Service::State Service::customStop()
{
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
