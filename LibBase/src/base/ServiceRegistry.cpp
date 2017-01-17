#include "ServiceRegistry.hpp"

#include <QThread>

namespace cutehmi {
namespace base {

ServiceRegistry & ServiceRegistry::Instance()
{
	static ServiceRegistry instance;
	return instance;
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

void ServiceRegistry::add(Service * service)
{
	m->services.append(service);
	if (service->state() == Service::STARTED)
		incStarted();
	else if (service->state() == Service::STOPPED)
		incStopped();
	emit serviceListChanged();
}

void ServiceRegistry::clear()
{
//	for (Service * service : m->services)
//		service->disconnect()
	m->services.clear();
	m->stopped = 0;
	m->started = 0;
	emit stoppedChanged();
	emit startedChanged();
	emit serviceListChanged();
}

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

ServiceRegistry::ServiceRegistry(QObject * parent):
	QObject(parent),
	m(new Members(this))
{
}

ServiceRegistry::~ServiceRegistry()
{
	if (stopped() > 0)
		qWarning("Destroying ServiceRegistry instance while not all registered services have been stopped.");
	clear();
}

void ServiceRegistry::stateChangeHandler(Service::state_t oldState, Service::state_t newState)
{
	if (oldState == Service::STARTED)
		decStarted();
	if (newState == Service::STARTED)
		incStarted();
	if (oldState == Service::STOPPED)
		decStopped();
	if (newState == Service::STOPPED)
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

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
