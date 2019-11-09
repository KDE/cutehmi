#include <cutehmi/services/ServiceManager.hpp>

namespace cutehmi {
namespace services {

constexpr int ServiceManager::INITIAL_MAX_ACTIVE_SERVICES;
constexpr int ServiceManager::INITIAL_REPAIR_INTERVAL;

int ServiceManager::maxActiveServices() const
{
	return m->maxActiveServices;
}

void ServiceManager::setMaxActiveServices(int maxActiveServices)
{
	if (m->maxActiveServices != maxActiveServices) {
		m->maxActiveServices = maxActiveServices;
		emit maxActiveServicesChanged();
	}
}

int ServiceManager::repairInterval() const
{
	return m->repairInterval;
}

void ServiceManager::setRepairInterval(int repairInterval)
{
	if (m->repairInterval != repairInterval) {
		m->repairInterval = repairInterval;
		emit repairIntervalChanged();
	}
}

void ServiceManager::add(Service * service)
{
	m->services->append(service);
}

void ServiceManager::remove(Service * service)
{
	m->services->remove(service);
}

void ServiceManager::manage(Service * service)
{
	// Temporary used to store lambda connections.
	QMetaObject::Connection connection;

	// Check whether service is impolite or polite.
	if (!service->serviceable().value<Serviceable *>()->transitionToYielding()) {
		// If service is impolite, then simply activate it.
		connection = QObject::connect(& service->stateInterface()->yielding(), & QState::entered, [service]() {
			service->activate();
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);
	} else {
		// If service is polite, then manage yielding.
		connection = QObject::connect(& service->stateInterface()->active(), & QState::exited, [this]() {
			if (m->yieldingServices.empty())
				m->activeServices--;
			else
				m->yieldingServices.dequeue()->activate();
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);

		connection = QObject::connect(& service->stateInterface()->yielding(), & QState::entered, [this, service]() {
			if (m->activeServices < m->maxActiveServices) {
				service->activate();
				m->activeServices++;
			} else
				m->yieldingServices.enqueue(service);
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);

		connection = QObject::connect(& service->stateInterface()->started(), & QState::exited, [this, service]() {
			m->yieldingServices.removeAll(service);
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);
	}

	// Manage repairing.
	if (service->serviceable().value<Serviceable *>()->transitionToBroken()) {
		QTimer * repairTimer = new QTimer(service->stateInterface());
		repairTimer->setSingleShot(true);
		QObject::connect(repairTimer, & QTimer::timeout, service, & Service::started);

		connection = QObject::connect(& service->stateInterface()->broken(), & QState::entered, [this, repairTimer]() {
			repairTimer->start(repairInterval());
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);

		connection = QObject::connect(& service->stateInterface()->broken(), & QState::exited, [repairTimer]() {
			repairTimer->stop();
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);
	}
}

void ServiceManager::leave(Service * service)
{
	while (m->stateInterfaceConnections.contains(service->stateInterface()))
		QObject::disconnect(m->stateInterfaceConnections.take(service->stateInterface()));

	if (service->stateInterface()->active().active())
		m->activeServices--;

	m->yieldingServices.removeAll(service);
}

void ServiceManager::start()
{
	for (int i = 0; i < m->services->rowCount(); i++) {
		if (m->services->at(i)->serviceable().value<Serviceable *>())
			m->services->at(i)->start();
	}
}

void ServiceManager::stop()
{
	for (int i = 0; i < m->services->rowCount(); i++)
		if (m->services->at(i)->serviceable().value<Serviceable *>())
			m->services->at(i)->stop();
}

ServiceManager::ServiceManager(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
