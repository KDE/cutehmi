#include "AbstractService.hpp"
#include "AbstractServiceController.hpp"
#include "ServiceAutoRepair.hpp"

#include <cutehmi/Notification.hpp>

#include <QCoreApplication>

namespace cutehmi {
namespace services {

constexpr int AbstractService::INITIAL_STOP_TIMEOUT;
constexpr int AbstractService::INITIAL_START_TIMEOUT;
constexpr int AbstractService::INITIAL_REPAIR_TIMEOUT;
constexpr const char * AbstractService::INITIAL_NAME;

AbstractService::~AbstractService()
{
	clearControllers();
}

int AbstractService::shutdownTimeout() const
{
	return m->shutdownTimeout;
}

void AbstractService::setShutdownTimeout(int shutdownTimeout)
{
	if (m->shutdownTimeout != shutdownTimeout) {
		m->shutdownTimeout = shutdownTimeout;
		emit shutdownTimeoutChanged();
	}
}

int AbstractService::stopTimeout() const
{
	return m->stopTimeout;
}

void AbstractService::setStopTimeout(int timeout)
{
	if (m->stopTimeout != timeout) {
		m->stopTimeout = timeout;
		emit stopTimeoutChanged();
	}
}

int AbstractService::startTimeout() const
{
	return m->startTimeout;
}

void AbstractService::setStartTimeout(int startTimeout)
{
	if (m->startTimeout != startTimeout) {
		m->startTimeout = startTimeout;
		emit startTimeoutChanged();
	}
}

int AbstractService::repairTimeout() const
{
	return m->repairTimeout;
}

void AbstractService::setRepairTimeout(int repairTimeout)
{
	if (m->repairTimeout != repairTimeout) {
		m->repairTimeout = repairTimeout;
		emit repairTimeoutChanged();
	}
}

QString AbstractService::name() const
{
	return m->name;
}

void AbstractService::setName(const QString & name)
{
	if (m->name != name) {
		m->name = name;
		emit nameChanged();
	}
}

QString AbstractService::status() const
{
	return m->status;
}

StateInterface * AbstractService::states() const
{
	return m->stateInterface;
}

QQmlListProperty<AbstractServiceController> AbstractService::defaultControllerList()
{
	return m->defaultControllerList;
}

QQmlListProperty<AbstractServiceController> AbstractService::controllerList()
{
	return m->controllerList;
}

void AbstractService::appendController(AbstractServiceController * controller)
{
	ControllerListAppend(& m->controllerList, controller);
}

void AbstractService::clearControllers()
{
	ControllerListClear(& m->controllerList);
}

void AbstractService::start()
{
	emit started();
}

void AbstractService::stop()
{
	emit stopped();
}

void AbstractService::activate()
{
	emit activated();
}

AbstractService::AbstractService(StateInterface * stateInterface, const QString & status, QObject * parent, const ControllersContainer * defaultControllers):
	QObject(parent),
	m(new Members(this, stateInterface, status, defaultControllers))
{
	m->stateInterface->setParent(this);

	for (auto && controller : *defaultControllerListData())
		appendController(controller);
}

const AbstractService::ControllersContainer & AbstractService::DefaultControllers()
{
	static ServiceAutoRepair defaultAutoRepair;
	static ControllersContainer defaultControllers = {& defaultAutoRepair};
	return defaultControllers;
}

const AbstractService::ControllersContainer & AbstractService::controllers() const
{
	return m->controllers;
}

AbstractService::ControllersContainer & AbstractService::controllers()
{
	return m->controllers;
}

void AbstractService::setStatus(const QString & status)
{
	if (m->status != status) {
		m->status = status;
		CUTEHMI_DEBUG(name() << ": " << status);
		emit statusChanged();
	}
}

workarounds::qt5compatibility::sizeType AbstractService::ControllerListCount(QQmlListProperty<AbstractServiceController> * property)
{
	return static_cast<ControllersContainer *>(property->data)->count();
}

AbstractServiceController * AbstractService::ControllerListAt(QQmlListProperty<AbstractServiceController> * property, workarounds::qt5compatibility::sizeType index)
{
	return static_cast<ControllersContainer *>(property->data)->value(index);
}

void AbstractService::ControllerListClear(QQmlListProperty<AbstractServiceController> * property)
{
	ControllersContainer * controllers = static_cast<ControllersContainer *>(property->data);
	AbstractService * service = static_cast<AbstractService *>(property->object);

	for (auto && controller : *controllers)
		controller->unsubscribe(service);

	controllers->clear();
}

void AbstractService::ControllerListAppend(QQmlListProperty<AbstractServiceController> * property, AbstractServiceController * value)
{
	AbstractService * service = static_cast<AbstractService *>(property->object);

	//<CuteHMI.Services-6.workaround target="Qt5" cause="missing">
	// Qt 5 misses QML_LIST_PROPERTY_ASSIGN_BEHAVIOR_REPLACE. Firstly we check whether the list is initialized with default
	// controllers (for a shortcut checking only the first one). Secondly we determine what is being appended by checking if
	// controller exists in defaultControllerList(). The list should usually be very short, so this shouldn't cause performance
	// problems.
	if (!static_cast<ControllersContainer *>(property->data)->empty() && !static_cast<ControllersContainer *>(service->defaultControllerList().data)->empty()
			&& static_cast<ControllersContainer *>(property->data)->constFirst() == static_cast<ControllersContainer *>(service->defaultControllerList().data)->constFirst()
			&& !static_cast<ControllersContainer *>(service->defaultControllerList().data)->contains(value))
		ControllerListClear(property);
	//</CuteHMI.Services-6.workaround>

	value->subscribe(service);

	static_cast<ControllersContainer *>(property->data)->append(value);
}

workarounds::qt5compatibility::sizeType AbstractService::DefaultControllerListCount(QQmlListProperty<AbstractServiceController> * property)
{
	const ControllersContainer * controllers = static_cast<const ControllersContainer *>(property->data);

	return controllers->count();
}

AbstractServiceController * AbstractService::DefaultControllerListAt(QQmlListProperty<AbstractServiceController> * property, workarounds::qt5compatibility::sizeType index)
{
	const ControllersContainer * controllers = static_cast<const ControllersContainer *>(property->data);

	return controllers->at(index);
}

const AbstractService::ControllersContainer * AbstractService::defaultControllerListData() const
{
	return static_cast<const ControllersContainer *>(m->defaultControllerList.data);
}

}
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
