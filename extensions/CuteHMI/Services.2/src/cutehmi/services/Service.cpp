#include <cutehmi/services/Service.hpp>

#include <cutehmi/services/ServiceManager.hpp>
#include <cutehmi/Notification.hpp>

#include <QCoreApplication>
#include <QThread>

namespace cutehmi {
namespace services {

constexpr int Service::INITIAL_STOP_TIMEOUT;
constexpr int Service::INITIAL_START_TIMEOUT;
constexpr int Service::INITIAL_REPAIR_TIMEOUT;
constexpr const char * Service::INITIAL_NAME;

Service::Service(QObject * parent):
	QObject(parent),
	m(new Members)
{
	ServiceManager::Instance().add(this);
	setStatus(DefaultStatus());
}

Service::~Service()
{
	stop();

	// Wait till either service stops or is interrupted.
	if (m->stateInterface)
		while (!m->stateInterface->stopped().active() && !m->stateInterface->interrupted().active()) {
			// Due to repair and start timeouts service may end up in broken state. Try to stop the service repeatedly.
			stop();

			// QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents) slows down shutdown, so execute this loop aggressively.
			QCoreApplication::processEvents();
		}

	if (m->serviceable)
		ServiceManager::Instance().leave(this);
	ServiceManager::Instance().remove(this);

	if (m->stateMachine)
		m->stateMachine->stop();
}

int Service::stopTimeout() const
{
	return m->stopTimeout;
}

void Service::setStopTimeout(int timeout)
{
	if (m->stopTimeout != timeout) {
		m->stopTimeout = timeout;
		emit stopTimeoutChanged();
	}
}

int Service::startTimeout() const
{
	return m->startTimeout;
}

void Service::setStartTimeout(int startTimeout)
{
	if (m->startTimeout != startTimeout) {
		m->startTimeout = startTimeout;
		emit startTimeoutChanged();
	}
}

int Service::repairTimeout() const
{
	return m->repairTimeout;
}

void Service::setRepairTimeout(int repairTimeout)
{
	if (m->repairTimeout != repairTimeout) {
		m->repairTimeout = repairTimeout;
		emit repairTimeoutChanged();
	}
}

QString Service::name() const
{
	return m->name;
}

void Service::setName(const QString & name)
{
	if (m->name != name) {
		m->name = name;
		emit nameChanged();
	}
}

QString Service::status() const
{
	return m->status;
}

void Service::setServiceable(QVariant serviceable)
{
	QObject * qobjectPtr = serviceable.value<QObject *>();
	Serviceable * serviceablePtr = dynamic_cast<Serviceable *>(qobjectPtr);
	if (qobjectPtr != nullptr && serviceablePtr == nullptr)
		CUTEHMI_WARNING("Object assigned as serviceable to '"  << name() << "' service does not implement 'cutehmi::services::Serviceable' interface.");

	if (m->serviceable != serviceablePtr) {
		if (m->serviceable)
			ServiceManager::Instance().leave(this);
		destroyStateMachine();
		if (serviceablePtr)
			initializeStateMachine(*serviceablePtr);
		m->serviceable = serviceablePtr;
		if (m->serviceable)
			ServiceManager::Instance().manage(this);
		else
			setStatus(DefaultStatus());
		emit serviceableChanged();
	}
}

QVariant Service::serviceable() const
{
	return QVariant::fromValue(m->serviceable);
}

QAbstractState * Service::findState(const QString & name) const
{
	if (m->stateInterface)
		return m->stateInterface->find(name);
	else
		CUTEHMI_WARNING("Service does not possess servicable object.");
	return nullptr;
}

void Service::start()
{
	emit started();
}

void Service::stop()
{
	emit stopped();
}

internal::StateInterface * Service::stateInterface()
{
	return m->stateInterface;
}

const internal::StateInterface * Service::stateInterface() const
{
	return m->stateInterface;
}

void Service::activate()
{
	emit activated();
}

void Service::setStatus(const QString & status)
{
	if (m->status != status) {
		m->status = status;
		if (m->serviceable)
			CUTEHMI_DEBUG(name() << ": " << status);
		emit statusChanged();
	}
}

QString & Service::DefaultStatus()
{
	static QString name = QObject::tr("Unmanaged");
	return name;
}

void Service::destroyStateMachine()
{
	if (m->stateMachine) {
		m->stateMachine->stop();
		m->stateMachine->deleteLater();
		m->stateMachine = nullptr;
		m->stateInterface = nullptr;
	}
}

void Service::initializeStateMachine(Serviceable & serviceable)
{
	try {
		m->stateMachine = new QStateMachine(this);
		m->stateInterface = new internal::StateInterface(m->stateMachine);

		connect(m->stateInterface, & internal::StateInterface::statusChanged, this, [this]() {
			setStatus(m->stateInterface->status());
		} );


		// Variable m->lastNotifiableState is used to prevent notification spam, i.e. when service fails to leave notifiable state
		// through intermediate, non-notifiable state (e.g. 'broken' is a notifiable state, 'repairing' is an intermediate state;
		// without the condition "Service 'XYZ' broke" message would be posted after each failed repair attempt).
		connect(& m->stateInterface->interrupted(), & QState::entered, this, [this]() {
			if (m->lastNotifiableState != & m->stateInterface->interrupted())
				Notification::Critical(tr("Stop sequence of '%1' service has been interrupted, because it took more than %2 [ms] to stop the service.").arg(name()).arg(stopTimeout()));
			m->lastNotifiableState = & m->stateInterface->interrupted();
		});
		connect(& m->stateInterface->started(), & QState::entered, this, [this]() {
			if (m->lastNotifiableState != & m->stateInterface->started())
				Notification::Info(tr("Service '%1' has started.").arg(name()));
			m->lastNotifiableState = & m->stateInterface->started();
		});
		connect(& m->stateInterface->stopped(), & QState::entered, this, [this]() {
			if (m->lastNotifiableState != & m->stateInterface->stopped())
				Notification::Info(tr("Service '%1' is stopped.").arg(name()));
			m->lastNotifiableState = & m->stateInterface->stopped();
		});
		connect(& m->stateInterface->broken(), & QState::entered, this, [this]() {
			if (m->lastNotifiableState != & m->stateInterface->broken())
				Notification::Critical(tr("Service '%1' broke.").arg(name()));
			m->lastNotifiableState = & m->stateInterface->broken();
		});


		// Configure timeouts.

		connect(& m->stateInterface->stopping(), & QState::entered, this, [this]() {
			if (stopTimeout() >= 0)
				m->timeoutTimer.start(stopTimeout());
		});
		// It's safer to stop timeout, so that it won't make false shot.
		connect(& m->stateInterface->stopping(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

		connect(& m->stateInterface->evacuating(), & QState::entered, this, [this]() {
			if (stopTimeout() >= 0)
				m->timeoutTimer.start(stopTimeout());
		});
		// It's safer to stop timeout, so that it won't make false shot.
		connect(& m->stateInterface->evacuating(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

		connect(& m->stateInterface->starting(), & QState::entered, this, [this]() {
			if (startTimeout() >= 0)
				m->timeoutTimer.start(startTimeout());
		});
		// It's safer to stop timeout, so that it won't make false shot.
		connect(& m->stateInterface->starting(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

		connect(& m->stateInterface->repairing(), & QState::entered, this, [this]() {
			if (repairTimeout() >= 0)
				m->timeoutTimer.start(repairTimeout());
		});
		// It's safer to stop timeout, so that it won't make false shot.
		connect(& m->stateInterface->repairing(), & QState::exited, & m->timeoutTimer, & QTimer::stop);


		m->stateInterface->stopped().assignProperty(m->stateInterface, "status", tr("Stopped"));
		m->stateInterface->interrupted().assignProperty(m->stateInterface, "status", tr("Interrupted"));
		m->stateInterface->starting().assignProperty(m->stateInterface, "status", tr("Starting"));
		m->stateInterface->started().assignProperty(m->stateInterface, "status", tr("Started"));
		m->stateInterface->idling().assignProperty(m->stateInterface, "status", tr("Idling"));
		m->stateInterface->yielding().assignProperty(m->stateInterface, "status", tr("Yielding"));
		m->stateInterface->active().assignProperty(m->stateInterface, "status", tr("Active"));
		m->stateInterface->stopping().assignProperty(m->stateInterface, "status", tr("Stopping"));
		m->stateInterface->broken().assignProperty(m->stateInterface, "status", tr("Broken"));
		m->stateInterface->repairing().assignProperty(m->stateInterface, "status", tr("Repairing"));
		m->stateInterface->evacuating().assignProperty(m->stateInterface, "status", tr("Evacuating"));


		m->stateMachine->addState(& m->stateInterface->stopped());
		m->stateMachine->addState(& m->stateInterface->interrupted());
		m->stateMachine->addState(& m->stateInterface->starting());
		m->stateMachine->addState(& m->stateInterface->started());
		m->stateMachine->addState(& m->stateInterface->stopping());
		m->stateMachine->addState(& m->stateInterface->broken());
		m->stateMachine->addState(& m->stateInterface->repairing());
		m->stateMachine->addState(& m->stateInterface->evacuating());
		m->stateMachine->setInitialState(& m->stateInterface->stopped());


		m->stateInterface->stopped().addTransition(this, & Service::started, & m->stateInterface->starting());
		m->stateInterface->started().addTransition(this, & Service::stopped, & m->stateInterface->stopping());
		m->stateInterface->broken().addTransition(this, & Service::started, & m->stateInterface->repairing());
		m->stateInterface->broken().addTransition(this, & Service::stopped, & m->stateInterface->evacuating());
		m->stateInterface->stopping().addTransition(& m->timeoutTimer, & QTimer::timeout, & m->stateInterface->interrupted());
		m->stateInterface->starting().addTransition(& m->timeoutTimer, & QTimer::timeout, & m->stateInterface->broken());
		m->stateInterface->repairing().addTransition(& m->timeoutTimer, & QTimer::timeout, & m->stateInterface->broken());
		m->stateInterface->yielding().addTransition(this, & Service::activated, & m->stateInterface->active());
		m->stateInterface->evacuating().addTransition(& m->timeoutTimer, & QTimer::timeout, & m->stateInterface->interrupted());


		addTransition(& m->stateInterface->starting(), & m->stateInterface->started(), serviceable.transitionToStarted());
		addTransition(& m->stateInterface->repairing(), & m->stateInterface->started(), serviceable.transitionToStarted());
		addTransition(& m->stateInterface->stopping(), & m->stateInterface->stopped(), serviceable.transitionToStopped());
		if (serviceable.transitionToBroken()) {
			addTransition(& m->stateInterface->starting(), & m->stateInterface->broken(), serviceable.transitionToBroken());
			addTransition(& m->stateInterface->started(), & m->stateInterface->broken(), serviceable.transitionToBroken());
			addTransition(& m->stateInterface->repairing(), & m->stateInterface->broken(), serviceable.transitionToBroken());
		}
		if (serviceable.transitionToIdling())
			addTransition(& m->stateInterface->active(), & m->stateInterface->idling(), serviceable.transitionToIdling());
		addTransition(& m->stateInterface->idling(), & m->stateInterface->yielding(), serviceable.transitionToYielding());
		addTransition(& m->stateInterface->evacuating(), & m->stateInterface->stopped(), serviceable.transitionToStopped());


		addStatuses(serviceable.configureBroken(& m->stateInterface->broken()));
		addStatuses(serviceable.configureStarted(& m->stateInterface->active(), & m->stateInterface->idling(), & m->stateInterface->yielding()));
		addStatuses(serviceable.configureStarting(& m->stateInterface->starting()));
		addStatuses(serviceable.configureStopping(& m->stateInterface->stopping()));
		addStatuses(serviceable.configureRepairing(& m->stateInterface->repairing()));
		addStatuses(serviceable.configureEvacuating(& m->stateInterface->evacuating()));

		m->stateMachine->start();
		QCoreApplication::processEvents();	// This is required in order to truly start state machine and prevent it from ignoring incoming events.
	} catch (const std::exception & e) {
		CUTEHMI_CRITICAL("Service '" << name() << "' could not initialize new state machine, because of the following exception: " << e.what());
	}
}

void Service::addTransition(QState * source, QState * target, std::unique_ptr<QAbstractTransition> transition)
{
	if (transition) {
		transition->setParent(source);
		transition->setTargetState(target);
		source->addTransition(transition.release());
	} else
		source->addTransition(target);
}

void Service::addStatuses(std::unique_ptr<Serviceable::ServiceStatuses> statuses)
{
	if (statuses)
		for (auto stateStatus = statuses->begin(); stateStatus != statuses->end(); ++stateStatus)
			stateStatus.key()->assignProperty(m->stateInterface, "status", stateStatus.value());
}

}
}

//(c)C: Copyright © 2019-2022, Michał Policht <michal@policht.pl>, Yuri Chornoivan <yurchor@ukr.net>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
