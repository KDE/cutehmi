 #include "../../../include/cutehmi/services/ServiceRegistry.hpp"

#include <QThread>

namespace cutehmi {
namespace services {

ServiceRegistry::ServiceRegistry(QObject * parent):
	QObject(parent),
	m(new Members(this))
{
}

ServiceRegistry::~ServiceRegistry()
{
	if (stopped() != count())
		CUTEHMI_LOG_WARNING("Destroying ServiceRegistry instance while not all registered services have been stopped.");
}

const QQmlListProperty<Service> & ServiceRegistry::serviceList() const
{
	return m->serviceList;
}

int ServiceRegistry::started() const
{
	return m->started;
}

int ServiceRegistry::stopped() const
{
	return m->stopped;
}

int ServiceRegistry::count() const
{
	return m->services.count();
}

void ServiceRegistry::add(Service * service)
{
	m->services.append(service);
	if (service->state() == Service::STARTED)
		incStarted();
	else if (service->state() == Service::STOPPED)
		incStopped();
	connect(service, & Service::stateChanged, this, & ServiceRegistry::stateChangeHandler);
	emit serviceListChanged();
}

//void ServiceRegistry::clear()
//{
//	for (Service * service : m->services)
//		service->disconnect(this);
//	m->services.clear();
//	m->stopped = 0;
//	m->started = 0;
//	emit stoppedChanged();
//	emit startedChanged();
//	emit serviceListChanged();
//}

void ServiceRegistry::start()
{
	for (Service * service : m->services)
		service->start();
}

void ServiceRegistry::stop()
{
	for (Service * service : m->services)
		service->stop();
}

void ServiceRegistry::stateChangeHandler(Service::State oldState, Service::State newState)
{
	if (oldState == Service::STOPPED)
		decStopped();
	else if (oldState == Service::STARTED)
		decStarted();

	if (newState == Service::STARTED)
		incStarted();
	else if (newState == Service::STOPPED)
		incStopped();
}

ServiceRegistry::Members::Members(QObject * obj):
	serviceList(obj, & services, ServiceRegistry::Count, ServiceRegistry::At),
	started(0),
	stopped(0)
{
}

void ServiceRegistry::incStarted()
{
	m->started++;
	emit startedChanged();
}

void ServiceRegistry::decStarted()
{
	m->started--;
	emit startedChanged();
}

void ServiceRegistry::incStopped()
{
	m->stopped++;
	emit stoppedChanged();
}

void ServiceRegistry::decStopped()
{
	m->stopped--;
	emit stoppedChanged();
}

int ServiceRegistry::Count(QQmlListProperty<Service> * property)
{
	return static_cast<ServicesContainer *>(property->data)->count();
}

Service * ServiceRegistry::At(QQmlListProperty<Service> * property, int index)
{
	return static_cast<ServicesContainer *>(property->data)->at(index);
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
