#include <cutehmi/services/ServiceGroup.hpp>
#include <cutehmi/services/ServiceAutoActivate.hpp>
#include <cutehmi/services/ServiceAutoStart.hpp>

#include "internal/ServiceStateMachine.hpp"
#include "internal/ServiceStateInterface.hpp"

#include <list>

namespace cutehmi {
namespace services {

void ServiceGroup::PostConditionCheckEvent(QStateMachine * stateMachine)
{
	if (stateMachine)
		stateMachine->postEvent(new QEvent(QEvent::Type(CONDITION_CHECK_EVENT)));
	else
		CUTEHMI_WARNING("Could not post condition check event, because given state machine pointer is null.");
}

ServiceGroup::ServiceGroup(QObject * parent):
	AbstractService(new internal::ServiceStateInterface, DefaultStatus(), parent, & DefaultControllers()),
	m(new Members(this))
{
	// Service status is read-only property, thus it is updated through state interface writebale double.
	connect(stateInterface(), & internal::ServiceStateInterface::statusChanged, this, & ServiceGroup::setStatus);

	connect(this, & ServiceGroup::stoppedCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::startingCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::startedCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::stoppingCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::brokenCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::repairingCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::evacuatingCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::interruptedCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::yieldingCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::activeCountChanged, this, & ServiceGroup::handleCounters);
	connect(this, & ServiceGroup::idlingCountChanged, this, & ServiceGroup::handleCounters);
}

ServiceGroup::~ServiceGroup()
{
	stateInterface()->shutdown();

	clearServices();
}

int ServiceGroup::startedCount() const
{
	return m->startedCount;
}

int ServiceGroup::startingCount() const
{
	return m->startingCount;
}

int ServiceGroup::stoppingCount() const
{
	return m->stoppingCount;
}

int ServiceGroup::stoppedCount() const
{
	return m->stoppedCount;
}

int ServiceGroup::brokenCount() const
{
	return m->brokenCount;
}

int ServiceGroup::repairingCount() const
{
	return m->repairingCount;
}

int ServiceGroup::evacuatingCount() const
{
	return m->evacuatingCount;
}

int ServiceGroup::interruptedCount() const
{
	return m->interruptedCount;
}

int ServiceGroup::activeCount() const
{
	return m->activeCount;
}

int ServiceGroup::yieldingCount() const
{
	return m->yieldingCount;
}

int ServiceGroup::idlingCount() const
{
	return m->idlingCount;
}

QQmlListProperty<ServiceGroupRule> ServiceGroup::ruleList()
{
	return m->ruleList;
}

void ServiceGroup::appendRule(ServiceGroupRule * rule)
{
	RuleListAppend(& m->ruleList, rule);
}

void ServiceGroup::clearRules()
{
	RuleListClear(& m->ruleList);
}

QQmlListProperty<AbstractService> ServiceGroup::serviceList()
{
	return m->serviceList;
}

void ServiceGroup::appendService(AbstractService * service)
{
	ServiceListAppend(& m->serviceList, service);
}

void ServiceGroup::clearServices()
{
	ServiceListClear(& m->serviceList);
}

void ServiceGroup::configureStarting(QState * starting, AssignStatusFunction assignStatus)
{
	configureStartingOrRepairing(starting, assignStatus);
}

void ServiceGroup::configureStarted(QState * active, const QState * idling, const QState * yielding, AssignStatusFunction assignStatus)
{
	Q_UNUSED(idling)
	Q_UNUSED(yielding)
	Q_UNUSED(assignStatus)

	active->setChildMode(QState::ParallelStates);

	for (auto && service : m->services) {
		QState * serviceSequence = new QState(active);

		QState * activateService = new QState(serviceSequence);
		connect(activateService, & QState::entered, service, & AbstractService::activate);

		std::list<std::unique_ptr<QAbstractTransition>> transitionList;
		for (auto && rule : m->rules) {
			auto transition = rule->conditionalTransition(ServiceGroupRule::SERVICE_ACTIVATE, service);
			if (transition)
				transitionList.push_back(std::move(transition));
		}

		QState * lastState = activateService;
		while (!transitionList.empty()) {
			auto transition = std::move(transitionList.back());
			transitionList.pop_back();
			transition->setTargetState(lastState);
			QState * conditionWait = new QState(serviceSequence);
			conditionWait->addTransition(transition.release());
			lastState = conditionWait;
		}

		serviceSequence->setInitialState(lastState);

		// Form a loop.
		activateService->addTransition(service->states()->startedStates()->yielding(), & QState::entered, lastState);
	}
}

void ServiceGroup::configureStopping(QState * stopping, AssignStatusFunction assignStatus)
{
	configureStoppingOrEvacuating(stopping, assignStatus);
}

void ServiceGroup::configureBroken(QState * broken, AssignStatusFunction assignStatus)
{
	Q_UNUSED(broken)
	Q_UNUSED(assignStatus)
}

void ServiceGroup::configureRepairing(QState * repairing, AssignStatusFunction assignStatus)
{
	configureStartingOrRepairing(repairing, assignStatus);

	// Services might have been repaired on their while ServiceGroup was in broken state, so make additional call to
	// handleCounters() whenever repairing state is re-entered.

	//<CuteHMI.Services-5.workaround target="Qt" cause="bug">
	// Function handleCounters() relies on values returned by QState::active(). Unfortunately `active` property is being set to true
	// only after the signal QState::entered() has been emitted, so if we connected QState::entered() to handleCounters, then despite
	// repairing state has been entered `active` property would return false. A workaround is to rely on QState::activeChanged()
	// signal instead of QState::entered().
	// Instead of:
	// connect(repairing, & QState::entered, this, & ServiceGroup::handleCounters);
	connect(repairing, & QState::activeChanged, this, & ServiceGroup::handleCounters);
	//</CuteHMI.Services-5.workaround target="Qt" cause="bug">
}

void ServiceGroup::configureEvacuating(QState * evacuating, AssignStatusFunction assignStatus)
{
	configureStoppingOrEvacuating(evacuating, assignStatus);
}

std::unique_ptr<QAbstractTransition> ServiceGroup::transitionToStarted() const
{
	return std::make_unique<QSignalTransition>(this, & ServiceGroup::groupStarted);
}

std::unique_ptr<QAbstractTransition> ServiceGroup::transitionToStopped() const
{
	return std::make_unique<QSignalTransition>(this, & ServiceGroup::groupStopped);
}

std::unique_ptr<QAbstractTransition> ServiceGroup::transitionToBroken() const
{
	return std::make_unique<QSignalTransition>(this, & ServiceGroup::groupBroken);
}

std::unique_ptr<QAbstractTransition> ServiceGroup::transitionToYielding() const
{
	return nullptr;
}

std::unique_ptr<QAbstractTransition> ServiceGroup::transitionToIdling() const
{
	return nullptr;
}

void ServiceGroup::classBegin()
{
	m->qmlBeingParsed = true;
}

void ServiceGroup::componentComplete()
{
	m->qmlBeingParsed = false;

	configureStateInterface();
}

void ServiceGroup::postConditionCheckEvent() const
{
	PostConditionCheckEvent(stateInterface()->stateMachine());
}

const AbstractService::ControllersContainer & ServiceGroup::DefaultControllers()
{
	static ServiceAutoActivate defaultAutoActivate;
	static ServiceAutoStart defaultAutoStart;
	static ControllersContainer defaultControllers = {& defaultAutoActivate, & defaultAutoStart};
	return defaultControllers;
}

void ServiceGroup::setStartedCount(int count)
{
	if (m->startedCount != count) {
		m->startedCount = count;
		emit startedCountChanged();
	}
}

void ServiceGroup::setStartingCount(int count)
{
	if (m->startingCount != count) {
		m->startingCount = count;
		emit startingCountChanged();
	}
}

void ServiceGroup::setStoppingCount(int count)
{
	if (m->stoppingCount != count) {
		m->stoppingCount = count;
		emit stoppingCountChanged();
	}
}

void ServiceGroup::setStoppedCount(int count)
{
	if (m->stoppedCount != count) {
		m->stoppedCount = count;
		emit stoppedCountChanged();
	}
}

void ServiceGroup::setBrokenCount(int count)
{
	if (m->brokenCount != count) {
		m->brokenCount = count;
		emit brokenCountChanged();
	}
}

void ServiceGroup::setRepairingCount(int count)
{
	if (m->repairingCount != count) {
		m->repairingCount = count;
		emit repairingCountChanged();
	}
}

void ServiceGroup::setEvacuatingCount(int count)
{
	if (m->evacuatingCount != count) {
		m->evacuatingCount = count;
		emit evacuatingCountChanged();
	}
}

void ServiceGroup::setInterruptedCount(int count)
{
	if (m->interruptedCount != count) {
		m->interruptedCount = count;
		emit interruptedCountChanged();
	}
}

void ServiceGroup::setActiveCount(int count)
{
	if (m->activeCount != count) {
		m->activeCount = count;
		emit activeCountChanged();
	}
}

void ServiceGroup::setYieldingCount(int count)
{
	if (m->yieldingCount != count) {
		m->yieldingCount = count;
		emit yieldingCountChanged();
	}
}

void ServiceGroup::setIdlingCount(int count)
{
	if (m->idlingCount != count) {
		m->idlingCount = count;
		emit idlingCountChanged();
	}
}

const ServiceGroup::RulesContainer & ServiceGroup::rules() const
{
	return m->rules;
}

ServiceGroup::RulesContainer & ServiceGroup::rules()
{
	return m->rules;
}

const ServiceGroup::ServicesContainer & ServiceGroup::services() const
{
	return m->services;
}

ServiceGroup::ServicesContainer & ServiceGroup::services()
{
	return m->services;
}

void ServiceGroup::handleCounters()
{
	if (states()->starting()->active())
		if (yieldingCount() == m->services.count())
			emit groupStarted();

	if (states()->repairing()->active())
		if (startedCount() == m->services.count())
			emit groupStarted();

	if (states()->stopping()->active() || states()->evacuating()->active())
		if (stoppedCount() == m->services.count())
			emit groupStopped();

	if (!states()->repairing()->active())
		if (brokenCount() > 0)
			emit groupBroken();

	if (interruptedCount() > 0)
		emit groupBroken();
}

QString & ServiceGroup::DefaultStatus()
{
	static QString name = QObject::tr("Uninitialized");
	return name;
}

workarounds::qt5compatibility::sizeType ServiceGroup::RuleListCount(QQmlListProperty<ServiceGroupRule> * property)
{
	return static_cast<RulesContainer *>(property->data)->count();
}

ServiceGroupRule * ServiceGroup::RuleListAt(QQmlListProperty<ServiceGroupRule> * property, workarounds::qt5compatibility::sizeType index)
{
	return static_cast<RulesContainer *>(property->data)->value(index);
}

void ServiceGroup::RuleListClear(QQmlListProperty<ServiceGroupRule> * property)
{
	static_cast<RulesContainer *>(property->data)->clear();
}

void ServiceGroup::RuleListAppend(QQmlListProperty<ServiceGroupRule> * property, ServiceGroupRule * value)
{
	static_cast<RulesContainer *>(property->data)->append(value);
}

workarounds::qt5compatibility::sizeType ServiceGroup::ServiceListCount(QQmlListProperty<AbstractService> * property)
{
	return static_cast<ServicesContainer *>(property->data)->count();
}

AbstractService * ServiceGroup::ServiceListAt(QQmlListProperty<AbstractService> * property, workarounds::qt5compatibility::sizeType index)
{
	return static_cast<ServicesContainer *>(property->data)->value(index);
}

void ServiceGroup::ServiceListClear(QQmlListProperty<AbstractService> * property)
{
	ServiceGroup * serviceGroup = static_cast<ServiceGroup *>(property->object);

	for (ServicesContainer::iterator it = serviceGroup->services().begin(); it != serviceGroup->services().end(); ++it)
		DeleteConnectionDataEntry(serviceGroup->m->serviceConnections, *it);

	serviceGroup->m->serviceConnections.clear();

	static_cast<ServicesContainer *>(property->data)->clear();

	if (!serviceGroup->stateInterface()->isShutdown())
		serviceGroup->stateInterface()->configureServiceable(serviceGroup);
}

void ServiceGroup::ServiceListAppend(QQmlListProperty<AbstractService> * property, AbstractService * value)
{
	ServiceGroup * serviceGroup = static_cast<ServiceGroup *>(property->object);

	ConnectionData * connectionData = CreateConnectionDataEntry(serviceGroup->m->serviceConnections, value);
	ConnectStateCounters(*connectionData, serviceGroup, value);

	static_cast<ServicesContainer *>(property->data)->append(value);

	if (!serviceGroup->m->qmlBeingParsed)
		serviceGroup->stateInterface()->configureServiceable(serviceGroup);
}

void ServiceGroup::ConnectStateCounters(ConnectionData & connectionData, ServiceGroup * serviceGroup, AbstractService * service)
{
	struct StateConnectionParams {
		QMetaObject::Connection * connection;
		int (ServiceGroup::*getter)(void) const;
		void (ServiceGroup::*setter)(int);
		union {
			QAbstractState * (StateInterface::*stateGetter)(void) const;
			QAbstractState * (StartedStateInterface::*startedStateGetter)(void) const;
		};
		bool startedSubstate = false;
	};

	QList<StateConnectionParams> stateConnectionParamsList;

	stateConnectionParamsList << StateConnectionParams{
		& connectionData.stopped,
		& ServiceGroup::stoppedCount,
		& ServiceGroup::setStoppedCount,
		{ & StateInterface::stopped },
	} << StateConnectionParams{
		& connectionData.starting,
		& ServiceGroup::startingCount,
		& ServiceGroup::setStartingCount,
		{ & StateInterface::starting },
	} << StateConnectionParams{
		& connectionData.started,
		& ServiceGroup::startedCount,
		& ServiceGroup::setStartedCount,
		{ & StateInterface::started },
	} << StateConnectionParams{
		& connectionData.stopping,
		& ServiceGroup::stoppingCount,
		& ServiceGroup::setStoppingCount,
		{ & StateInterface::stopping },
	} << StateConnectionParams{
		& connectionData.broken,
		& ServiceGroup::brokenCount,
		& ServiceGroup::setBrokenCount,
		{ & StateInterface::broken },
	} << StateConnectionParams{
		& connectionData.repairing,
		& ServiceGroup::repairingCount,
		& ServiceGroup::setRepairingCount,
		{ & StateInterface::repairing },
	} << StateConnectionParams{
		& connectionData.evacuating,
		& ServiceGroup::evacuatingCount,
		& ServiceGroup::setEvacuatingCount,
		{ & StateInterface::evacuating },
	} << StateConnectionParams{
		& connectionData.interrupted,
		& ServiceGroup::interruptedCount,
		& ServiceGroup::setInterruptedCount,
		{ & StateInterface::interrupted },
	};

	// Designated initializers are not available until C++20, so lets initialize started substates verbosely.
	StateConnectionParams yieldingConnectionParams;
	yieldingConnectionParams.connection = & connectionData.yielding;
	yieldingConnectionParams.getter = & ServiceGroup::yieldingCount;
	yieldingConnectionParams.setter = & ServiceGroup::setYieldingCount;
	yieldingConnectionParams.startedStateGetter = & StartedStateInterface::yielding;
	yieldingConnectionParams.startedSubstate = true;
	stateConnectionParamsList << yieldingConnectionParams;

	StateConnectionParams activeConnectionParams;
	activeConnectionParams.connection = & connectionData.active;
	activeConnectionParams.getter = & ServiceGroup::activeCount;
	activeConnectionParams.setter = & ServiceGroup::setActiveCount;
	activeConnectionParams.startedStateGetter = & StartedStateInterface::active;
	activeConnectionParams.startedSubstate = true;
	stateConnectionParamsList << activeConnectionParams;

	StateConnectionParams idlingConnectionParams;
	idlingConnectionParams.connection = & connectionData.idling;
	idlingConnectionParams.getter = & ServiceGroup::idlingCount;
	idlingConnectionParams.setter = & ServiceGroup::setIdlingCount;
	idlingConnectionParams.startedStateGetter = & StartedStateInterface::idling;
	idlingConnectionParams.startedSubstate = true;
	stateConnectionParamsList << idlingConnectionParams;

	for (auto && params : stateConnectionParamsList) {
		QAbstractState * state;
		if (params.startedSubstate)
			state = (service->states()->startedStates()->*params.startedStateGetter)();
		else
			state = (service->states()->*params.stateGetter)();

		auto getter = params.getter;
		auto setter = params.setter;
		*params.connection = connect(state, & QAbstractState::activeChanged, serviceGroup, [getter, setter, serviceGroup](bool active) {
			(serviceGroup->*setter)((serviceGroup->*getter)() + (active ? 1 : -1));
		});
	}
}

ServiceGroup::ConnectionData * ServiceGroup::CreateConnectionDataEntry(ServiceConnectionsContainer & serviceConnections, AbstractService * service)
{
	ConnectionData * connectionData = new ConnectionData;
	serviceConnections.insert(service, connectionData);
	return connectionData;
}

void ServiceGroup::DeleteConnectionDataEntry(ServiceConnectionsContainer & serviceConnections, AbstractService * service)
{
	ConnectionData * connectionData = serviceConnections.value(service);
	disconnect(connectionData->stopped);
	disconnect(connectionData->starting);
	disconnect(connectionData->started);
	disconnect(connectionData->stopping);
	disconnect(connectionData->broken);
	disconnect(connectionData->repairing);
	disconnect(connectionData->evacuating);
	disconnect(connectionData->interrupted);
	disconnect(connectionData->yielding);
	disconnect(connectionData->active);
	disconnect(connectionData->idling);
	delete connectionData;
}

internal::ServiceStateInterface * ServiceGroup::stateInterface() const
{
	return static_cast<internal::ServiceStateInterface *>(states());
}

void ServiceGroup::configureStateInterface()
{
	stateInterface()->configureServiceable(this);
	emit initialized();
}

void ServiceGroup::configureStoppingOrEvacuating(QState * state, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	state->setChildMode(QState::ParallelStates);

	for (auto && service : m->services) {
		QState * serviceSequence = new QState(state);

		QState * serviceStopping = new QState(serviceSequence);
		connect(serviceStopping, & QState::entered, service, & AbstractService::stop);

		std::list<std::unique_ptr<QAbstractTransition>> transitionList;
		for (auto && rule : m->rules) {
			auto transition = rule->conditionalTransition(ServiceGroupRule::SERVICE_STOP, service);
			if (transition)
				transitionList.push_back(std::move(transition));
		}

		QState * lastState = serviceStopping;
		while (!transitionList.empty()) {
			auto transition = std::move(transitionList.back());
			transitionList.pop_back();
			transition->setTargetState(lastState);
			QState * conditionWait = new QState(serviceSequence);
			conditionWait->addTransition(transition.release());
			lastState = conditionWait;
		}

		serviceSequence->setInitialState(lastState);
	}
}

void ServiceGroup::configureStartingOrRepairing(QState * state, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	state->setChildMode(QState::ParallelStates);

	for (auto && service : m->services) {
		QState * serviceSequence = new QState(state);

		QState * startService = new QState(serviceSequence);
		connect(startService, & QState::entered, service, & AbstractService::start);

		std::list<std::unique_ptr<QAbstractTransition>> transitionList;
		for (auto && rule : m->rules) {
			auto transition = rule->conditionalTransition(ServiceGroupRule::SERVICE_START, service);
			if (transition)
				transitionList.push_back(std::move(transition));
		}

		QState * lastState = startService;
		while (!transitionList.empty()) {
			auto transition = std::move(transitionList.back());
			transitionList.pop_back();
			transition->setTargetState(lastState);
			QState * conditionWait = new QState(serviceSequence);
			connect(conditionWait, & QState::entered, this, & ServiceGroup::postConditionCheckEvent);
			conditionWait->addTransition(transition.release());
			lastState = conditionWait;
		}

		serviceSequence->setInitialState(lastState);
	}
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
