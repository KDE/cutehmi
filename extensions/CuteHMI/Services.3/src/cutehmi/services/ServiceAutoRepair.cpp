#include <cutehmi/services/ServiceAutoRepair.hpp>
#include <cutehmi/services/AbstractService.hpp>

#include <QJSEngine>
#include <QTimer>

namespace cutehmi {
namespace services {

constexpr const char * ServiceAutoRepair::INITIAL_INTERVAL_FUNCTION;

ServiceAutoRepair::ServiceAutoRepair(QObject * parent):
	AbstractServiceController(parent),
	m(new Members{
	INITIAL_INITIAL_INTERVAL,
	QJSValue::UndefinedValue,
	{}})
{
	setIntervalFunction(QString(INITIAL_INTERVAL_FUNCTION));
}

ServiceAutoRepair::~ServiceAutoRepair()
{
	auto services = m->serviceData.keys();
	for (auto && service : services)
		clearServiceEntry(service);
}

QJSValue ServiceAutoRepair::intervalFunction() const
{
	return m->intervalFunction;
}

int ServiceAutoRepair::initialInterval() const
{
	return m->initialInterval;
}

void ServiceAutoRepair::setInitialInterval(int initialInterval)
{
	if (m->initialInterval != initialInterval) {
		m->initialInterval = initialInterval;
		emit initialIntervalChanged();
	}
}

void ServiceAutoRepair::setIntervalFunction(const QJSValue & intervalFunction)
{
	if (m->intervalFunction.strictlyEquals(intervalFunction))
		return;

	m->intervalFunction = intervalFunction;

	emit intervalFunctionChanged();
}

void ServiceAutoRepair::setIntervalFunction(const QString & intervalFunction)
{
	QJSValue function = JSEngine().evaluate(intervalFunction);
	if (function.isCallable())
		setIntervalFunction(function);
	else
		CUTEHMI_WARNING("String assigned to 'intervalFunction' does not evaluate to a function.");
}

void ServiceAutoRepair::subscribe(AbstractService * service)
{
	if (m->serviceData.contains(service)) {
		CUTEHMI_WARNING("Service " << service << " is already subscribed to " << this << ".");
		return;
	}

	ServiceEntry * serviceEntry = new ServiceEntry;
	serviceEntry->timer = new QTimer(this);
	serviceEntry->timer->setSingleShot(true);
	serviceEntry->timer->setInterval(initialInterval());

	// Reset interval when the service was in started or starting state (all states that lead to broken, except of repairing).
	serviceEntry->startedEnteredConnection = connectResetIntervalOnStateEntered(service->states()->started(), serviceEntry->timer);
	serviceEntry->startedChangedConnection = connect(service->states(), & StateInterface::startedChanged, serviceEntry->timer, [this, service]() {
		ServiceEntry * serviceEntry = m->serviceData.value(service);
		CUTEHMI_ASSERT(serviceEntry != nullptr, "serviceEntry can not be nullptr");
		disconnect(serviceEntry->startedEnteredConnection);
		serviceEntry->startedEnteredConnection = connectResetIntervalOnStateEntered(service->states()->started(), serviceEntry->timer);
	});
	serviceEntry->startingEnteredConnection = connectResetIntervalOnStateEntered(service->states()->starting(), serviceEntry->timer);
	serviceEntry->startingChangedConnection = connect(service->states(), & StateInterface::startingChanged, serviceEntry->timer, [this, service]() {
		ServiceEntry * serviceEntry = m->serviceData.value(service);
		CUTEHMI_ASSERT(serviceEntry != nullptr, "serviceEntry can not be nullptr");
		disconnect(serviceEntry->startingEnteredConnection);
		serviceEntry->startingEnteredConnection = connectResetIntervalOnStateEntered(service->states()->starting(), serviceEntry->timer);
	});

	// Set new interval, when the service entered repairing state (if service fails to start the new interval will be used).
	serviceEntry->repairingEnteredConnection = connectRepairingEntered(service, serviceEntry->timer);
	serviceEntry->repairingChangedConnection = connect(service->states(), & StateInterface::repairingChanged, serviceEntry->timer, [this, service]() {
		ServiceEntry * serviceEntry = m->serviceData.value(service);
		CUTEHMI_ASSERT(serviceEntry != nullptr, "serviceEntry can not be nullptr");
		disconnect(serviceEntry->repairingEnteredConnection);
		serviceEntry->repairingEnteredConnection = connectRepairingEntered(service, serviceEntry->timer);
	});

	// Trigger the timer, when the service enters broken state.
	serviceEntry->brokenEnteredConnection = connectBrokenEntered(service, serviceEntry->timer);
	serviceEntry->brokenChangedConnection = connect(service->states(), & StateInterface::brokenChanged, serviceEntry->timer, [this, service]() {
		ServiceEntry * serviceEntry = m->serviceData.value(service);
		CUTEHMI_ASSERT(serviceEntry != nullptr, "serviceEntry can not be nullptr");
		disconnect(serviceEntry->brokenEnteredConnection);
		serviceEntry->brokenEnteredConnection = connectBrokenEntered(service, serviceEntry->timer);
	});

	// Trigger the repair when the timer timeout is reached.
	connect(serviceEntry->timer, & QTimer::timeout, service, & AbstractService::start);

	m->serviceData.insert(service, serviceEntry);
}

void ServiceAutoRepair::unsubscribe(AbstractService * service)
{
	if (!m->serviceData.contains(service)) {
		CUTEHMI_WARNING("Can not unsubscribe service " << service << " as it was not subscribed to " << this << ".");
		return;
	}

	clearServiceEntry(service);
}

QJSEngine & ServiceAutoRepair::JSEngine()
{
	static QJSEngine engine;
	return engine;
}

QMetaObject::Connection ServiceAutoRepair::connectResetIntervalOnStateEntered(const QAbstractState * state, QTimer * timer)
{
	return connect(state, & QAbstractState::entered, timer, [this, timer] {
		timer->setInterval(initialInterval());
	});
}

QMetaObject::Connection ServiceAutoRepair::connectRepairingEntered(const AbstractService * service, QTimer * timer)
{
	return connect(service->states()->repairing(), & QAbstractState::entered, timer, [this, timer] {
		QJSValue newInterval = intervalFunction().isNumber() ? intervalFunction() : intervalFunction().call({timer->interval()});
		if (!newInterval.isNumber())
			CUTEHMI_CRITICAL("Expression given as 'intervalFunction' does not evaluate to a number.");
		else
			timer->setInterval(newInterval.toInt());
	});
}

QMetaObject::Connection ServiceAutoRepair::connectBrokenEntered(const AbstractService * service, QTimer * timer)
{
	return connect(service->states()->broken(), & QAbstractState::entered, timer, [timer] {
		timer->start();
	});

}

void ServiceAutoRepair::clearServiceEntry(AbstractService * service)
{
	ServiceEntry * serviceEntry = m->serviceData.take(service);
	disconnect(serviceEntry->startingEnteredConnection);
	disconnect(serviceEntry->startingChangedConnection);
	disconnect(serviceEntry->startedEnteredConnection);
	disconnect(serviceEntry->startedChangedConnection);
	disconnect(serviceEntry->repairingEnteredConnection);
	disconnect(serviceEntry->repairingChangedConnection);
	disconnect(serviceEntry->brokenEnteredConnection);
	disconnect(serviceEntry->brokenChangedConnection);
	disconnect(serviceEntry->timer, & QTimer::timeout, service, & AbstractService::start);
	serviceEntry->timer->deleteLater();
	delete serviceEntry;
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
