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
