#include "ServiceStateInterface.hpp"
#include "ServiceStartedStateInterface.hpp"
#include "stateInterfaceHelpers.hpp"

#include <cutehmi/services/Serviceable.hpp>
#include <cutehmi/services/AbstractService.hpp>

#include <cutehmi/Notification.hpp>

#include <QDeadlineTimer>

namespace cutehmi {
namespace services {
namespace internal {

ServiceStateInterface::ServiceStateInterface():
	m(new Members(this))
{
	initializePersistentStates();
}

ServiceStateInterface::~ServiceStateInterface()
{
	m->stateMachine->deleteLater();
	m->stateMachine = nullptr;
}

QString ServiceStateInterface::status() const
{
	return m->status;
}

void ServiceStateInterface::setStatus(const QString & status)
{
	if (m->status != status) {
		m->status = status;
		emit statusChanged(status);
	}
}

bool ServiceStateInterface::isShutdown() const
{
	return m->isShutdown;
}

ServiceStateMachine * ServiceStateInterface::stateMachine() const
{
	return m->stateMachine;
}

void ServiceStateInterface::configureServiceable(Serviceable * serviceable)
{
	m->stateMachine->stop();

	startedInterface()->resetEphemericStates();
	resetEphemericStates();

	if (serviceable) {
		setUpStopped(false, *serviceable);
		setUpStarting(false, *serviceable);
		setUpStarted(false, *serviceable);	// Handles also startedInterface().
		setUpStopping(false, *serviceable);
		setUpBroken(false, *serviceable);
		setUpRepairing(false, *serviceable);
		setUpEvacuating(false, *serviceable);
		setUpInterrupted(false, *serviceable);

		m->stateMachine->start(); // Note: start() function is shadowed by internal::ServiceStateMachine.
	}
}

QAbstractState * ServiceStateInterface::stopped() const
{
	return m->stopped.persistent;
}

QAbstractState * ServiceStateInterface::starting() const
{
	return m->starting.persistent;
}

QAbstractState * ServiceStateInterface::started() const
{
	return m->started.persistent;
}

QAbstractState * ServiceStateInterface::stopping() const
{
	return m->stopping.persistent;
}

QAbstractState * ServiceStateInterface::broken() const
{
	return m->broken.persistent;
}

QAbstractState * ServiceStateInterface::repairing() const
{
	return m->repairing.persistent;
}

QAbstractState * ServiceStateInterface::evacuating() const
{
	return m->evacuating.persistent;
}

QAbstractState * ServiceStateInterface::interrupted() const
{
	return m->interrupted.persistent;
}

StartedStateInterface * ServiceStateInterface::startedStates() const
{
	return m->started.interface;
}

void ServiceStateInterface::reconfigureStopped(const Serviceable & serviceable)
{
	m->stateMachine->stop();

	setUpStopped(true, serviceable);

	m->stateMachine->start(); // Note: start() function is shadowed by internal::ServiceStateMachine.
}

void ServiceStateInterface::reconfigureStarting(Serviceable & serviceable)
{
	m->stateMachine->stop();

	setUpStarting(true, serviceable);

	m->stateMachine->start(); // Note: start() function is shadowed by internal::ServiceStateMachine.
}

void ServiceStateInterface::reconfigureStarted(Serviceable & serviceable)
{
	m->stateMachine->stop();

	setUpStarted(true, serviceable);

	m->stateMachine->start(); // Note: start() function is shadowed by internal::ServiceStateMachine.
}

void ServiceStateInterface::reconfigureStopping(Serviceable & serviceable)
{
	m->stateMachine->stop();

	setUpStopping(true, serviceable);

	m->stateMachine->start(); // Note: start() function is shadowed by internal::ServiceStateMachine.
}

void ServiceStateInterface::reconfigureBroken(Serviceable & serviceable)
{
	m->stateMachine->stop();

	setUpBroken(true, serviceable);

	m->stateMachine->start(); // Note: start() function is shadowed by internal::ServiceStateMachine.
}

void ServiceStateInterface::reconfigureRepairing(Serviceable & serviceable)
{
	m->stateMachine->stop();

	setUpRepairing(true, serviceable);

	m->stateMachine->start(); // Note: start() function is shadowed by internal::ServiceStateMachine.
}

void ServiceStateInterface::reconfigureEvacuating(Serviceable & serviceable)
{
	m->stateMachine->stop();

	setUpEvacuating(true, serviceable);

	m->stateMachine->start(); // Note: start() function is shadowed by internal::ServiceStateMachine.
}

void ServiceStateInterface::reconfigureInterrupted(const Serviceable & serviceable)
{
	m->stateMachine->stop();

	setUpInterrupted(true, serviceable);

	m->stateMachine->start(); // Note: start() function is shadowed by internal::ServiceStateMachine.
}

void ServiceStateInterface::replaceTransitionToStarted(const Serviceable & serviceable)
{
	clearTransition(m->starting, 0);
	clearTransition(m->repairing, 0);

	addStartingTransition(0, serviceable);
	addRepairingTransition(0, serviceable);
}

void ServiceStateInterface::replaceTransitionToStopped(const Serviceable & serviceable)
{
	clearTransition(m->stopping, 0);
	clearTransition(m->evacuating, 0);

	addStoppingTransition(0, serviceable);
	addEvacuatingTransition(0, serviceable);
}

void ServiceStateInterface::replaceTransitionToBroken(const Serviceable & serviceable)
{
	clearTransition(m->starting, 1);
	clearTransition(m->started, 1);
	clearTransition(m->repairing, 2);

	addStartingTransition(1, serviceable);
	addStartedTransition(1, serviceable);
	addRepairingTransition(2, serviceable);
}

void ServiceStateInterface::replaceTransitionToYielding(const Serviceable & serviceable)
{
	startedInterface()->replaceTransitionToYielding(serviceable);
}

void ServiceStateInterface::replaceTransitionToIdling(const Serviceable & serviceable)
{
	startedInterface()->replaceTransitionToIdling(serviceable);
}

void ServiceStateInterface::shutdown()
{
	// Stop the service.
	service()->stop();

	// Wait till either service stops or it is interrupted, or deadline passes.
	QDeadlineTimer shutdownTimer(service()->shutdownTimeout());
	while (!stopped()->active() && !interrupted()->active()) {
		if (shutdownTimer.hasExpired()) {
			CUTEHMI_CRITICAL("Shutdown sequence has been interrupted, because it took more than " << service()->shutdownTimeout() << " [ms] to stop the service.");
			break;
		}

		// Due to repair and start timeouts service may end up in broken state. Try to stop the service repeatedly.
		service()->stop();

		// QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents) slows down shutdown, so execute this loop aggressively.
		QCoreApplication::processEvents();
	}

	m->stateMachine->stop();

	m->isShutdown = true;
}

QState * ServiceStateInterface::startingPersistent() const
{
	return m->starting.persistent;
}

QState * ServiceStateInterface::startedPersistent() const
{
	return m->started.persistent;
}

ServiceStartedStateInterface * ServiceStateInterface::startedInterface() const
{
	return m->started.interface;
}

QState * ServiceStateInterface::stoppingPersistent() const
{
	return m->stopping.persistent;
}

QState * ServiceStateInterface::stoppedPersistent() const
{
	return m->stopped.persistent;
}

QState * ServiceStateInterface::brokenPersistent() const
{
	return m->broken.persistent;
}

QState * ServiceStateInterface::repairingPersistent() const
{
	return m->repairing.persistent;
}

QState * ServiceStateInterface::evacuatingPersistent() const
{
	return m->evacuating.persistent;
}

QState * ServiceStateInterface::interruptedPersistent() const
{
	return m->interrupted.persistent;
}

QState * ServiceStateInterface::startingEphemeric() const
{
	return m->starting.ephemeric;
}

QState * ServiceStateInterface::startedEphemeric() const
{
	return m->started.ephemeric;
}

QState * ServiceStateInterface::stoppingEphemeric() const
{
	return m->stopping.ephemeric;
}

QState * ServiceStateInterface::stoppedEphemeric() const
{
	return m->stopped.ephemeric;
}

QState * ServiceStateInterface::brokenEphemeric() const
{
	return m->broken.ephemeric;
}

QState * ServiceStateInterface::repairingEphemeric() const
{
	return m->repairing.ephemeric;
}

QState * ServiceStateInterface::evacuatingEphemeric() const
{
	return m->evacuating.ephemeric;
}

QState * ServiceStateInterface::interruptedEphemeric() const
{
	return m->interrupted.ephemeric;
}

QAbstractTransition *& ServiceStateInterface::startingTransition(int index)
{
	return m->starting.transitions[index];
}

QAbstractTransition *& ServiceStateInterface::startedTransition(int index)
{
	return m->started.transitions[index];
}

QAbstractTransition * const & ServiceStateInterface::startedTransition(int index) const
{
	return m->started.transitions[index];
}

QAbstractTransition *& ServiceStateInterface::stoppingTransition(int index)
{
	return m->stopping.transitions[index];
}

QAbstractTransition * const & ServiceStateInterface::stoppingTransition(int index) const
{
	return m->stopping.transitions[index];
}

QAbstractTransition *& ServiceStateInterface::stoppedTransition(int index)
{
	return m->stopped.transitions[index];
}

QAbstractTransition * const & ServiceStateInterface::stoppedTransition(int index) const
{
	return m->stopped.transitions[index];
}

QAbstractTransition *& ServiceStateInterface::brokenTransition(int index)
{
	return m->broken.transitions[index];
}

QAbstractTransition * const & ServiceStateInterface::brokenTransition(int index) const
{
	return m->broken.transitions[index];
}

QAbstractTransition *& ServiceStateInterface::repairingTransition(int index)
{
	return m->repairing.transitions[index];
}

QAbstractTransition * const & ServiceStateInterface::repairingTransition(int index) const
{
	return m->repairing.transitions[index];
}

QAbstractTransition *& ServiceStateInterface::evacuatingTransition(int index)
{
	return m->evacuating.transitions[index];
}

QAbstractTransition * const & ServiceStateInterface::evacuatingTransition(int index) const
{
	return m->evacuating.transitions[index];
}

void ServiceStateInterface::initializePersistentStates()
{
	m->starting.persistent->setObjectName("starting");
	m->starting.persistent->assignProperty(this, "status", tr("Starting"));

	m->started.persistent->setObjectName("started");
	m->started.persistent->assignProperty(this, "status", tr("Started"));

	m->stopping.persistent->setObjectName("stopping");
	m->stopping.persistent->assignProperty(this, "status", tr("Stopping"));

	m->stopped.persistent->setObjectName("stopped");
	m->stopped.persistent->assignProperty(this, "status", tr("Stopped"));

	m->broken.persistent->setObjectName("broken");
	m->broken.persistent->assignProperty(this, "status", tr("Broken"));

	m->repairing.persistent->setObjectName("repairing");
	m->repairing.persistent->assignProperty(this, "status", tr("Repairing"));

	m->evacuating.persistent->setObjectName("evacuating");
	m->evacuating.persistent->assignProperty(this, "status", tr("Evacuating"));

	m->interrupted.persistent->setObjectName("interrupted");
	m->interrupted.persistent->assignProperty(this, "status", tr("Interrupted"));
}

void ServiceStateInterface::resetEphemericStates()
{
	resetStoppedEphemeric();
	resetStartingEphemeric();
	resetStartedEphemeric();
	resetStoppingEphemeric();
	resetBrokenEphemeric();
	resetRepairingEphemeric();
	resetEvacuatingEphemeric();
	resetInterruptedEphemeric();
}

void ServiceStateInterface::resetStartingEphemeric()
{
	clearTransition(m->starting, 0);
	clearTransition(m->starting, 1);
	clearTransition(m->starting, 2);

	recreateState(m->starting, "starting.ephemeric");
}

void ServiceStateInterface::resetStartedEphemeric()
{
	clearTransition(m->started, 0);
	clearTransition(m->started, 1);

	// Temporarily make persistent state a parent, so that states are not deleted along with deleted ephemeric parent.
	startedInterface()->setStarted(startedPersistent());

	recreateState(m->started, "started.ephemeric");

	startedInterface()->setStarted(startedEphemeric());
	m->started.ephemeric->setInitialState(startedInterface()->yielding());
}

void ServiceStateInterface::resetStoppingEphemeric()
{
	clearTransition(m->stopping, 0);
	clearTransition(m->stopping, 1);

	recreateState(m->stopping, "stopping.ephemeric");
}

void ServiceStateInterface::resetStoppedEphemeric()
{
	clearTransition(m->stopped, 0);

	recreateState(m->stopped, "stopped.ephemeric");
}

void ServiceStateInterface::resetBrokenEphemeric()
{
	clearTransition(m->broken, 0);
	clearTransition(m->broken, 1);

	recreateState(m->broken, "broken.ephemeric");
}

void ServiceStateInterface::resetRepairingEphemeric()
{
	clearTransition(m->repairing, 0);
	clearTransition(m->repairing, 1);
	clearTransition(m->repairing, 2);

	recreateState(m->repairing, "repairing.ephemeric");
}

void ServiceStateInterface::resetEvacuatingEphemeric()
{
	clearTransition(m->evacuating, 0);
	clearTransition(m->evacuating, 1);

	recreateState(m->evacuating, "evacuating.ephemeric");
}

void ServiceStateInterface::resetInterruptedEphemeric()
{
	recreateState(m->interrupted, "interrupted.ephemeric");
}

void ServiceStateInterface::setUpStopped(bool reconfigure, const Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->evacuating, 0);
		clearTransition(m->stopping, 0);

		// Reset the state.
		resetStoppedEphemeric();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addEvacuatingTransition(0, serviceable);
		addStoppingTransition(0, serviceable);
	}
	// Outgoing transitions.
	addStoppedTransition(0);

	// Notify if this state was entered.
	connect(stoppedEphemeric(), & QState::entered, this, [this]() {
		if (m->lastNotifiableState != stoppedEphemeric())
			Notification::Info(tr("Service '%1' is stopped.").arg(service()->name()));
		m->lastNotifiableState = stoppedEphemeric();
	});

	// Set this state as initial state.
	m->stateMachine->setInitialState(stoppedPersistent());
}

void ServiceStateInterface::setUpStarting(bool reconfigure, Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->stopped, 0);

		// Reset the state.
		resetStartingEphemeric();
	}

	// Configure timeout.
	connect(startingEphemeric(), & QState::entered, this, [this]() {
		if (service()->startTimeout() >= 0)
			m->timeoutTimer.start(service()->startTimeout());
	});
	// It's safer to stop timeout, so that it won't make a false shot.
	connect(startingEphemeric(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addStoppedTransition(0);
	}
	// Outgoing transitions.
	addStartingTransition(0, serviceable);
	addStartingTransition(1, serviceable);
	addStartingTransition(2, serviceable);

	// Allow servicable to configure this state.
	serviceable.configureStarting(m->starting.ephemeric, [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});
}

void ServiceStateInterface::setUpStarted(bool reconfigure, Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->starting, 0);
		clearTransition(m->repairing, 0);

		// Reset the state.
		resetStartedEphemeric();
	}

	// Set up substates (they will be also reset if necessary).
	startedInterface()->setUpActive(reconfigure, serviceable);
	startedInterface()->setUpYielding(reconfigure, serviceable);
	startedInterface()->setUpIdling(reconfigure, serviceable);

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addStartedTransition(0, serviceable);
		addRepairingTransition(0, serviceable);
	}
	// Outgoing transitions.
	addStartedTransition(0, serviceable);
	addStartedTransition(1, serviceable);

	// Allow servicable to configure this state.
	serviceable.configureStarted(startedInterface()->activeEphemeric(), startedInterface()->idlingEphemeric(), startedInterface()->yieldingEphemeric(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});

	// Notify if this state was entered.
	connect(startedEphemeric(), & QState::entered, this, [this]() {
		if (m->lastNotifiableState != startedEphemeric())
			Notification::Info(tr("Service '%1' has started.").arg(service()->name()));
		m->lastNotifiableState = startedEphemeric();
	});
}

void ServiceStateInterface::setUpStopping(bool reconfigure, Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->started, 0);

		// Reset the state.
		resetStoppingEphemeric();
	}

	// Configure timeout.
	connect(stoppingEphemeric(), & QState::entered, this, [this]() {
		if (service()->stopTimeout() >= 0)
			m->timeoutTimer.start(service()->stopTimeout());
	});
	// It's safer to stop timeout, so that it won't make a false shot.
	connect(stoppingEphemeric(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addStartedTransition(0, serviceable);
	}
	// Outgoing transitions.
	addStoppingTransition(0, serviceable);
	addStoppingTransition(1, serviceable);

	// Allow servicable to configure this state.
	serviceable.configureStopping(stoppingEphemeric(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});
}

void ServiceStateInterface::setUpBroken(bool reconfigure, Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->started, 1);
		clearTransition(m->starting, 1);
		clearTransition(m->starting, 2);
		clearTransition(m->repairing, 1);
		clearTransition(m->repairing, 2);

		// Reset the state.
		resetBrokenEphemeric();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addStartedTransition(1, serviceable);
		addStartingTransition(1, serviceable);
		addStartingTransition(2, serviceable);
		addRepairingTransition(1, serviceable);
		addRepairingTransition(2, serviceable);
	}
	// Outgoing transitions.
	addBrokenTransition(0);
	addBrokenTransition(1);

	// Allow servicable to configure this state.
	serviceable.configureBroken(brokenEphemeric(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});

	// Notify if this state was entered.
	connect(brokenEphemeric(), & QState::entered, this, [this]() {
		if (m->lastNotifiableState != brokenEphemeric())
			Notification::Critical(tr("Service '%1' broke.").arg(service()->name()));
		m->lastNotifiableState = brokenEphemeric();
	});
}

void ServiceStateInterface::setUpRepairing(bool reconfigure, Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->broken, 0);

		// Reset the state.
		resetRepairingEphemeric();
	}

	// Configure timeout.
	connect(repairingEphemeric(), & QState::entered, this, [this]() {
		if (service()->repairTimeout() >= 0)
			m->timeoutTimer.start(service()->repairTimeout());
	});
	// It's safer to stop timeout, so that it won't make false shot.
	connect(repairingEphemeric(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addBrokenTransition(0);
	}
	// Outgoing transitions.
	addRepairingTransition(0, serviceable);
	addRepairingTransition(1, serviceable);
	addRepairingTransition(2, serviceable);

	// Allow servicable to configure this state.
	serviceable.configureRepairing(repairingEphemeric(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});
}

void ServiceStateInterface::setUpEvacuating(bool reconfigure, Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->broken, 1);

		// Reset the state.
		resetEvacuatingEphemeric();
	}

	// Configure timeout.
	connect(evacuatingEphemeric(), & QState::entered, this, [this]() {
		if (service()->stopTimeout() >= 0)
			m->timeoutTimer.start(service()->stopTimeout());
	});
	// It's safer to stop timeout, so that it won't make false shot.
	connect(evacuatingEphemeric(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addBrokenTransition(1);
	}
	// Outgoing transitions.
	addEvacuatingTransition(0, serviceable);
	addEvacuatingTransition(1, serviceable);

	// Allow servicable to configure this state.
	serviceable.configureEvacuating(evacuatingEphemeric(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});
}

void ServiceStateInterface::setUpInterrupted(bool reconfigure, const Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->evacuating, 1);
		clearTransition(m->stopping, 1);

		// Reset the state.
		resetInterruptedEphemeric();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addEvacuatingTransition(1, serviceable);
		addStoppingTransition(1, serviceable);
	}
	// Outgoing transitions.
	// None.

	// Notify if this state was entered.
	connect(interruptedEphemeric(), & QState::entered, this, [this]() {
		if (m->lastNotifiableState != interruptedEphemeric())
			Notification::Critical(tr("Stop sequence of '%1' service has been interrupted, because it took more than %2 [ms] to stop the service.").arg(service()->name()).arg(service()->stopTimeout()));
		m->lastNotifiableState = interruptedEphemeric();
	});
}

void ServiceStateInterface::addStoppedTransition(int index)
{
	auto state = stoppedEphemeric();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			stoppedTransition(index) = state->addTransition(service(), & AbstractService::started, startingEphemeric());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
}

void ServiceStateInterface::addStartingTransition(int index, const Serviceable & serviceable)
{
	auto state = startingEphemeric();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			startingTransition(index) = addServiceableTransition(state, startedEphemeric(), serviceable.transitionToStarted(), true);
			break;
		case 1:
			startingTransition(index) = addServiceableTransition(state, brokenEphemeric(), serviceable.transitionToBroken());
			break;
		case 2:
			startingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, brokenEphemeric());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}

}

void ServiceStateInterface::addStartedTransition(int index, const Serviceable & serviceable)
{
	auto state = startedEphemeric();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			startedTransition(index) = state->addTransition(service(), & AbstractService::stopped, stoppingEphemeric());
			break;
		case 1:
			startedTransition(index) = addServiceableTransition(state, brokenEphemeric(), serviceable.transitionToBroken());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
}

void ServiceStateInterface::addStoppingTransition(int index, const Serviceable & serviceable)
{
	auto state = stoppingEphemeric();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			stoppingTransition(index) = addServiceableTransition(state, stoppedEphemeric(), serviceable.transitionToStopped(), true);
			break;
		case 1:
			stoppingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, interruptedEphemeric());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
}

void ServiceStateInterface::addBrokenTransition(int index)
{
	auto state = brokenEphemeric();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			brokenTransition(index) = state->addTransition(service(), & AbstractService::started, repairingEphemeric());
			break;
		case 1:
			brokenTransition(index) = state->addTransition(service(), & AbstractService::stopped, evacuatingEphemeric());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
}

void ServiceStateInterface::addRepairingTransition(int index, const Serviceable & serviceable)
{
	auto state = repairingEphemeric();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			repairingTransition(index) = addServiceableTransition(state, startedEphemeric(), serviceable.transitionToStarted(), true);
			break;
		case 1:
			repairingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, brokenEphemeric());
			break;
		case 2:
			repairingTransition(index) = addServiceableTransition(state, brokenEphemeric(), serviceable.transitionToBroken());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
}

void ServiceStateInterface::addEvacuatingTransition(int index, const Serviceable & serviceable)
{
	auto state = evacuatingEphemeric();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			evacuatingTransition(index) = addServiceableTransition(state, stoppedEphemeric(), serviceable.transitionToStopped(), true);
			break;
		case 1:
			evacuatingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, interruptedEphemeric());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
}

void ServiceStateInterface::addInterrputedTransition(int index)
{
	auto state = interruptedEphemeric();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
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
