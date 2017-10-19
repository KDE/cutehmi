#include "../../include/modbus/Service.hpp"
#include "../../include/modbus/Client.hpp"

#include <base/Prompt.hpp>

#include <QTimer>
#include <QCoreApplication>
#include <QAbstractEventDispatcher>

#include <limits>

namespace cutehmi {
namespace modbus {

Service::Service(const QString & name, Client * client, QObject * parent):
	services::Service(name, parent),
	m(new Members(client))
{
	QObject::connect(m->client, & Client::error, this, & Service::handleError);

	QState * stoppedState = new QState;
	QState * startingState = new QState;
	QState * startedState = new QState;
	QState * stoppingState = new QState;
	QState * brokenState = new QState;
	QState * brokenWaitState = new QState;

	stoppedState->addTransition(this, SIGNAL(customStartRequested()), startingState);
	QObject::connect(stoppedState, & QState::entered, this, & Service::onStoppedEntered);

	startingState->addTransition(this, SIGNAL(customStopRequested()), stoppingState);
	startingState->addTransition(m->thread.get(), SIGNAL(ran()), startedState);
	startingState->addTransition(m->thread.get(), SIGNAL(finished()), brokenWaitState);
	startingState->addTransition(m->client, SIGNAL(error(cutehmi::base::ErrorInfo)), brokenState);
	startingState->addTransition(m->client, SIGNAL(disconnected()), brokenState);
	QObject::connect(startingState, & QState::entered, this, & Service::startServiceThread);

	startedState->addTransition(this, SIGNAL(customStopRequested()), stoppingState);
	startedState->addTransition(m->client, SIGNAL(error(cutehmi::base::ErrorInfo)), brokenState);
	startedState->addTransition(m->client, SIGNAL(disconnected()), brokenState);
	startedState->addTransition(m->thread.get(), SIGNAL(finished()), brokenWaitState);
	QObject::connect(startedState, & QState::entered, this, & Service::onStartedEntered);

	stoppingState->addTransition(m->thread.get(), SIGNAL(finished()), stoppedState);
	QObject::connect(stoppingState, & QState::entered, this, & Service::stopServiceThread);

	brokenState->addTransition(m->thread.get(), SIGNAL(finished()), brokenWaitState);
	QObject::connect(brokenState, & QState::entered, this, & Service::onBrokenEntered);

	brokenWaitState->addTransition(this, SIGNAL(customStopRequested()), stoppedState);
	brokenWaitState->addTransition(this, SIGNAL(brokenTimeoutTriggered()), startingState);
	QObject::connect(brokenWaitState, & QState::entered, this, & Service::onBrokenWaitEntered);
	QObject::connect(brokenWaitState, & QState::exited, this, & Service::onBrokenWaitExited);

	m->sm.addState(stoppedState);
	m->sm.addState(startingState);
	m->sm.addState(startedState);
	m->sm.addState(stoppingState);
	m->sm.addState(brokenState);
	m->sm.addState(brokenWaitState);

	// m->sm requires running event loop to transition between states, thus currently it is started in customStart() as dirty workaround.
	m->sm.setInitialState(startingState);
}

Service::~Service()
{
	if (state() != STOPPED)
		stop();
	// Process pending signals to put m->sm into stoppedState.
	QCoreApplication::eventDispatcher()->processEvents(QEventLoop::AllEvents);
}

unsigned long Service::sleep() const
{
	return m->thread->sleep();
}

void Service::setSleep(unsigned long sleep)
{
	m->thread->setSleep(sleep);
}

Service::state_t Service::customStart()
{
	setState(STARTING);
	if (m->sm.isRunning())
		emit customStartRequested();
	else
		m->sm.start();
	return state();
}

Service::state_t Service::customStop()
{
	setState(STOPPING);
	emit customStopRequested();
	return state();
}

void Service::startServiceThread()
{
	CUTEHMI_MODBUS_QDEBUG("Starting modbus service thread...");
	m->thread->start();
}

void Service::stopServiceThread()
{
	CUTEHMI_MODBUS_QDEBUG("Stopping modbus service thread...");
	m->thread->stop();
	m->thread->quit();
	m->thread->wait();
}

void Service::onStartedEntered()
{
	setState(STARTED);
	base::Notification::Note(tr("Modbus service '%1' started.").arg(name()));
	m->brokenServiceWait = INITIAL_BROKEN_SERVICE_WAIT;
}

void Service::onStoppedEntered()
{
	setState(STOPPED);
	base::Notification::Note(tr("Modbus service '%1' stopped.").arg(name()));
}

void Service::onBrokenEntered()
{
	setState(BROKEN);
	base::Notification::Critical(tr("Modbus service '%1' is in broken state.").arg(name()));
	stopServiceThread();
}

void Service::onBrokenWaitEntered()
{
	setState(BROKEN);
	if (m->client->isConnected())
		m->client->disconnect();
	base::Notification::Note(tr("Modbus service '%1' is scheduled to restart in %2 seconds...").arg(name()).arg(m->brokenServiceWait / 1000 ));
	QTimer::singleShot(m->brokenServiceWait, this, SIGNAL(brokenTimeoutTriggered()));
	m->brokenServiceWait = std::min(static_cast<int>(std::min(MAX_BROKEN_SERVICE_WAIT, static_cast<long>(std::numeric_limits<int>::max()))), m->brokenServiceWait * 2);
}

void Service::onBrokenWaitExited()
{
	setState(REPAIRING);
}

void Service::handleError(cutehmi::base::ErrorInfo errorInfo)
{
	base::Notification::Critical(errorInfo);
}

constexpr long Service::MAX_BROKEN_SERVICE_WAIT;
constexpr int Service::INITIAL_BROKEN_SERVICE_WAIT;

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
