#include <cutehmi/services/ServiceManager.hpp>

namespace cutehmi {
namespace services {

constexpr int ServiceManager::INITIAL_MAX_ACTIVE_SERVICES;
constexpr int ServiceManager::INITIAL_REPAIR_INTERVAL;

ServiceManager * ServiceManager::create(QQmlEngine * qmlEngine, QJSEngine * jsEngine)
{
	Q_UNUSED(jsEngine)

	ServiceManager * instance = & Instance();
	qmlEngine->setObjectOwnership(instance, QQmlEngine::CppOwnership);

	return instance;
}

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

int ServiceManager::runningCount() const
{
	return m->runningCount;
}

ServiceListModel * ServiceManager::model() const
{
	return m->model.get();
}

void ServiceManager::add(Service * service)
{
	m->model->append(service);
}

void ServiceManager::remove(Service * service)
{
	m->model->remove(service);
}

void ServiceManager::manage(Service * service)
{
	// Temporary used to store lambda connections.
	QMetaObject::Connection connection;

	// Check whether service is impolite or polite.
	if (!service->serviceable().value<Serviceable *>()->transitionToYielding()) {
		// If service is impolite, then simply activate it.
		connection = QObject::connect(& service->stateInterface()->yielding(), & QState::entered, service, & Service::activate);
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);
	} else {
		// If service is polite, then manage yielding.
		connection = QObject::connect(& service->stateInterface()->active(), & QState::exited, this, [this]() {
			if (m->yieldingServices.empty())
				m->activeServices--;
			else
				m->yieldingServices.dequeue()->activate();
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);

		connection = QObject::connect(& service->stateInterface()->yielding(), & QState::entered, this, [this, service]() {
			if (m->activeServices < m->maxActiveServices) {
				service->activate();
				m->activeServices++;
			} else
				m->yieldingServices.enqueue(service);
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);

		connection = QObject::connect(& service->stateInterface()->started(), & QState::exited, this, [this, service]() {
			m->yieldingServices.removeAll(service);
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);
	}

	// Manage repairing.
	if (service->serviceable().value<Serviceable *>()->transitionToBroken()) {
		QTimer * repairTimer = new QTimer(service->stateInterface());
		repairTimer->setSingleShot(true);
		QObject::connect(repairTimer, & QTimer::timeout, service, & Service::started);

		connection = QObject::connect(& service->stateInterface()->broken(), & QState::entered, repairTimer, [this, repairTimer]() {
			repairTimer->start(repairInterval());
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);

		connection = QObject::connect(& service->stateInterface()->broken(), & QState::exited, repairTimer, [repairTimer]() {
			repairTimer->stop();
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);
	}

	// Count running services.
	connection = QObject::connect(& service->stateInterface()->stopped(), & QState::exited, this, [this]() {
		m->runningCount++;
		emit runningCountChanged();
	});
	m->stateInterfaceConnections.insert(service->stateInterface(), connection);
	connection = QObject::connect(& service->stateInterface()->stopped(), & QState::entered, this, [this]() {
		m->runningCount--;
		emit runningCountChanged();
	});
	m->stateInterfaceConnections.insert(service->stateInterface(), connection);
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
	for (int i = 0; i < m->model->rowCount(); i++) {
		if (m->model->at(i)->serviceable().value<Serviceable *>())
			m->model->at(i)->start();
	}
}

void ServiceManager::stop()
{
	for (int i = 0; i < m->model->rowCount(); i++)
		if (m->model->at(i)->serviceable().value<Serviceable *>())
			m->model->at(i)->stop();
}

ServiceManager::ServiceManager(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

}
}

//(c)C: Copyright © 2019-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
