#include <cutehmi/services/StateInterface.hpp>

namespace cutehmi {
namespace services {

QAbstractState * StateInterface::stopped() const
{
	return m->stopped;
}

QAbstractState * StateInterface::starting() const
{
	return m->starting;
}

QAbstractState * StateInterface::started() const
{
	return m->started;
}

QAbstractState * StateInterface::stopping() const
{
	return m->stopping;
}

QAbstractState * StateInterface::broken() const
{
	return m->broken;
}

QAbstractState * StateInterface::repairing() const
{
	return m->repairing;
}

QAbstractState * StateInterface::evacuating() const
{
	return m->evacuating;
}

QAbstractState * StateInterface::interrupted() const
{
	return m->interrupted;
}

StartedStateInterface * StateInterface::startedStates() const
{
	return m->startedStateInterface;
}

QAbstractState * StateInterface::findState(const QString & name) const
{
	for (auto && state : {
					m->stopped,
					m->starting,
					m->started,
					m->stopping,
					m->broken,
					m->repairing,
					m->evacuating,
					m->interrupted
			}) {
		QAbstractState * child = state->findChild<QAbstractState *>(name);
		if (child)
			return child;
	}

	return nullptr;
}

StateInterface::StateInterface():
	m(new Members{
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	new StartedStateInterface(this)})
{
}


void StateInterface::setStopped(QAbstractState * stopped)
{
	if (m->stopped != stopped) {
		m->stopped = stopped;
		emit stoppedChanged();
	}
}

void StateInterface::setStarting(QAbstractState * starting)
{
	if (m->starting != starting) {
		m->starting = starting;
		emit startingChanged();
	}
}

void StateInterface::setStarted(QAbstractState * started, QAbstractState * yielding, QAbstractState * active, QAbstractState * idling)
{
	m->startedStateInterface->setYielding(yielding);
	m->startedStateInterface->setActive(active);
	m->startedStateInterface->setIdling(idling);
	if (m->started != started) {
		m->started = started;
		emit startedChanged();
	}
}

void StateInterface::setStopping(QAbstractState * stopping)
{
	if (m->stopping != stopping) {
		m->stopping = stopping;
		emit stoppingChanged();
	}
}

void StateInterface::setBroken(QAbstractState * broken)
{
	if (m->broken != broken) {
		m->broken = broken;
		emit brokenChanged();
	}
}

void StateInterface::setRepairing(QAbstractState * repairing)
{
	if (m->repairing != repairing) {
		m->repairing = repairing;
		emit repairingChanged();
	}
}

void StateInterface::setEvacuating(QAbstractState * evacuating)
{
	if (m->evacuating != evacuating) {
		m->evacuating = evacuating;
		emit evacuatingChanged();
	}
}

void StateInterface::setInterrupted(QAbstractState * interrupted)
{
	if (m->interrupted != interrupted) {
		m->interrupted = interrupted;
		emit interruptedChanged();
	}
}

}
}
