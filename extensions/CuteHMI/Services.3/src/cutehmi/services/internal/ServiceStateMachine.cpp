#include "ServiceStateMachine.hpp"

#include <cutehmi/Notification.hpp>
#include <cutehmi/services/Service.hpp>
#include <cutehmi/services/AbstractService.hpp>


namespace cutehmi {
namespace services {
namespace internal {

template<std::size_t N>
QAbstractTransition * getTransition(const std::array<QAbstractTransition *, N> & transitions, int index)
{
	if (index < 0 || static_cast<std::size_t>(index) >= transitions.size()) {
		CUTEHMI_WARNING("There is no transition with index " << index << ".");
		return nullptr;
	}

	return transitions[index];
}

template<typename T>
void clearTransition(T & stateData, std::size_t index)
{
	if (stateData.transitions[index] != nullptr) {
		if (stateData.state != nullptr)
			stateData.state->removeTransition(stateData.transitions[index]);
		stateData.transitions[index]->deleteLater();
		stateData.transitions[index] = nullptr;
	}
}

QAbstractTransition * addServiceableTransition(QState * source, QState * target, std::unique_ptr<QAbstractTransition> serviceableTransition, bool unconditionalIfNull = false)
{
	QAbstractTransition * transition = nullptr;

	if (serviceableTransition) {
		transition = serviceableTransition.release();
		transition->setTargetState(target);
		source->addTransition(transition);
	} else if (unconditionalIfNull)
		transition = source->addTransition(target);

	return transition;
}

ServiceStateMachine::ServiceStateMachine(AbstractService * service, Serviceable * serviceable):
	QStateMachine(service),
	m(new Members{
	service,
	serviceable,
	QTimer{},	// C++17 mandatory copy elision of explicit ctor call (see: https://en.cppreference.com/w/cpp/language/copy_elision).
	nullptr,
	{ nullptr, {} },
	{ nullptr, {} },
	{ nullptr, {} },
	{ nullptr, {} },
	{ nullptr, {} },
	{ nullptr, {} },
	{ nullptr, {} },
	{ nullptr, {} },
	{}})
{
	resetStoppedState();
	resetStartingState();
	resetStartedState();
	resetStoppingState();
	resetBrokenState();
	resetRepairingState();
	resetEvacuatingState();
	resetInterruptedState();

	setUpStopped(false);
	setUpStarting(false);
	setUpStarted(false);
	setUpStopping(false);
	setUpBroken(false);
	setUpRepairing(false);
	setUpEvacuating(false);
	setUpInterrupted(false);
}

QState * ServiceStateMachine::startingState()
{
	return m->starting.state;
}

const QState * ServiceStateMachine::startingState() const
{
	return m->starting.state;
}

ServiceStateMachine::StartedState * ServiceStateMachine::startedState()
{
	return m->started.state;
}

const ServiceStateMachine::StartedState * ServiceStateMachine::startedState() const
{
	return m->started.state;
}

QState * ServiceStateMachine::stoppingState()
{
	return m->stopping.state;
}

const QState * ServiceStateMachine::stoppingState() const
{
	return m->stopping.state;
}

QState * ServiceStateMachine::stoppedState()
{
	return m->stopped.state;
}

const QState * ServiceStateMachine::stoppedState() const
{
	return m->stopped.state;
}

QState * ServiceStateMachine::brokenState()
{
	return m->broken.state;
}

const QState * ServiceStateMachine::brokenState() const
{
	return m->broken.state;
}

QState * ServiceStateMachine::repairingState()
{
	return m->repairing.state;
}

const QState * ServiceStateMachine::repairingState() const
{
	return m->repairing.state;
}

QState * ServiceStateMachine::evacuatingState()
{
	return m->evacuating.state;
}

const QState * ServiceStateMachine::evacuatingState() const
{
	return m->evacuating.state;
}

QState * ServiceStateMachine::interruptedState()
{
	return m->interrupted.state;
}

const QState * ServiceStateMachine::interruptedState() const
{
	return m->interrupted.state;
}

QAbstractTransition *& ServiceStateMachine::startingTransition(int index)
{
	return m->starting.transitions[index];
}

QAbstractTransition *& ServiceStateMachine::startedTransition(int index)
{
	return m->started.transitions[index];
}

QAbstractTransition * const & ServiceStateMachine::startedTransition(int index) const
{
	return m->started.transitions[index];
}

QAbstractTransition *& ServiceStateMachine::stoppingTransition(int index)
{
	return m->stopping.transitions[index];
}

QAbstractTransition * const & ServiceStateMachine::stoppingTransition(int index) const
{
	return m->stopping.transitions[index];
}

QAbstractTransition *& ServiceStateMachine::stoppedTransition(int index)
{
	return m->stopped.transitions[index];
}

QAbstractTransition * const & ServiceStateMachine::stoppedTransition(int index) const
{
	return m->stopped.transitions[index];
}

QAbstractTransition *& ServiceStateMachine::brokenTransition(int index)
{
	return m->broken.transitions[index];
}

QAbstractTransition * const & ServiceStateMachine::brokenTransition(int index) const
{
	return m->broken.transitions[index];
}

QAbstractTransition *& ServiceStateMachine::repairingTransition(int index)
{
	return m->repairing.transitions[index];
}

QAbstractTransition * const & ServiceStateMachine::repairingTransition(int index) const
{
	return m->repairing.transitions[index];
}

QAbstractTransition *& ServiceStateMachine::evacuatingTransition(int index)
{
	return m->evacuating.transitions[index];
}

QAbstractTransition * const & ServiceStateMachine::evacuatingTransition(int index) const
{
	return m->evacuating.transitions[index];
}

QString ServiceStateMachine::status() const
{
	return m->status;
}

void ServiceStateMachine::setStatus(const QString & status)
{
	if (m->status != status) {
		m->status = status;
		emit statusChanged(status);
	}
}

AbstractService * ServiceStateMachine::service() const
{
	return m->service;
}

Serviceable * ServiceStateMachine::serviceable() const
{
	return m->serviceable;
}

QAbstractState * ServiceStateMachine::findState(const QString & name)
{
	QAbstractState * child = findChild<QAbstractState *>(name);
	if (child)
		return child;

	return nullptr;
}

QAbstractState * ServiceStateMachine::state(int index)
{
	switch (index) {
		case STOPPED_STATE:
			return m->stopped.state;
		case STARTING_STATE:
			return m->starting.state;
		case STARTED_STATE:
			return m->started.state;
		case STOPPING_STATE:
			return m->stopping.state;
		case BROKEN_STATE:
			return m->broken.state;
		case REPAIRING_STATE:
			return m->repairing.state;
		case EVACUATING_STATE:
			return m->evacuating.state;
		case INTERRUPTED_STATE:
			return m->interrupted.state;
		default:
			CUTEHMI_CRITICAL("No state is associated with index " << index << " within service state machine.");
	}

	return nullptr;
}

QAbstractTransition * ServiceStateMachine::transition(int stateIndex, int transitionIndex)
{
	switch (stateIndex) {
		case STOPPED_STATE:
			return getTransition(m->stopped.transitions, transitionIndex);
		case STARTING_STATE:
			return getTransition(m->starting.transitions, transitionIndex);
		case STARTED_STATE:
			return getTransition(m->started.transitions, transitionIndex);
		case STOPPING_STATE:
			return getTransition(m->stopping.transitions, transitionIndex);
		case BROKEN_STATE:
			return getTransition(m->broken.transitions, transitionIndex);
		case REPAIRING_STATE:
			return getTransition(m->repairing.transitions, transitionIndex);
		case EVACUATING_STATE:
			return getTransition(m->evacuating.transitions, transitionIndex);
		case INTERRUPTED_STATE:
			return getTransition(m->interrupted.transitions, transitionIndex);
		default:
			CUTEHMI_WARNING("No state is associated with index " << stateIndex << " within service state machine.");
	}

	return nullptr;
}

void ServiceStateMachine::start()
{
	QStateMachine::start();
	QCoreApplication::processEvents();	// This is required in order to truly start state machine and prevent it from ignoring incoming events.
}

void ServiceStateMachine::shutdown()
{
	// Wait till either service stops or it is interrupted.
	while (!stoppedState()->active() && !interruptedState()->active()) {
		// Due to repair and start timeouts service may end up in broken state. Try to stop the service repeatedly.
		m->service->stop();

		// QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents) slows down shutdown, so execute this loop aggressively.
		QCoreApplication::processEvents();
	}
}

void ServiceStateMachine::reconfigureStopped()
{
	setUpStopped(true);
}

void ServiceStateMachine::reconfigureStarting()
{
	setUpStarting(true);
}

void ServiceStateMachine::reconfigureStarted()
{
	setUpStarted(true);
}

void ServiceStateMachine::reconfigureStopping()
{
	setUpStopping(true);
}

void ServiceStateMachine::reconfigureBroken()
{
	setUpBroken(true);
}

void ServiceStateMachine::reconfigureRepairing()
{
	setUpRepairing(true);
}

void ServiceStateMachine::reconfigureEvacuating()
{
	setUpEvacuating(true);
}

void ServiceStateMachine::reconfigureInterrupted()
{
	setUpInterrupted(true);
}

void ServiceStateMachine::replaceTransitionToStarted()
{
	clearTransition(m->starting, 0);
	clearTransition(m->repairing, 0);

	addStartingTransition(0);
	addRepairingTransition(0);
}

void ServiceStateMachine::replaceTransitionToStopped()
{
	clearTransition(m->stopping, 0);
	clearTransition(m->evacuating, 0);

	addStoppingTransition(0);
	addEvacuatingTransition(0);
}

void ServiceStateMachine::replaceTransitionToBroken()
{
	clearTransition(m->starting, 1);
	clearTransition(m->started, 1);
	clearTransition(m->repairing, 2);

	addStartingTransition(1);
	addStartedTransition(1);
	addRepairingTransition(2);
}

void ServiceStateMachine::replaceTransitionToYielding()
{
	startedState()->replaceTransitionToYielding();
}

void ServiceStateMachine::replaceTransitionToIdling()
{
	startedState()->replaceTransitionToIdling();
}

void ServiceStateMachine::resetStartingState()
{
	clearState(m->starting.state);
	m->starting.state = new QState(this);
	m->starting.state->setObjectName("starting");
	m->starting.state->assignProperty(this, "status", tr("Starting"));

	emit startingStateChanged();
}

void ServiceStateMachine::resetStartedState()
{
	clearState(m->started.state);
	m->started.state = new StartedState(this);
	m->started.state->setObjectName("started");
	m->started.state->assignProperty(this, "status", tr("Started"));
	m->started.state->yieldingState()->assignProperty(this, "status", tr("Yielding"));
	m->started.state->activeState()->assignProperty(this, "status", tr("Active"));
	m->started.state->idlingState()->assignProperty(this, "status", tr("Idling"));

	emit startedStateAndSubstatesChanged();
}

void ServiceStateMachine::resetStoppingState()
{
	clearState(m->stopping.state);
	m->stopping.state = new QState(this);
	m->stopping.state->setObjectName("stopping");
	m->stopping.state->assignProperty(this, "status", tr("Stopping"));

	emit stoppingStateChanged();
}

void ServiceStateMachine::resetStoppedState()
{
	clearState(m->stopped.state);
	m->stopped.state = new QState(this);
	m->stopped.state->setObjectName("stopped");
	m->stopped.state->assignProperty(this, "status", tr("Stopped"));

	emit stoppedStateChanged();
}

void ServiceStateMachine::resetBrokenState()
{
	clearState(m->broken.state);
	m->broken.state = new QState(this);
	m->broken.state->setObjectName("broken");
	m->broken.state->assignProperty(this, "status", tr("Broken"));

	emit brokenStateChanged();
}

void ServiceStateMachine::resetRepairingState()
{
	clearState(m->repairing.state);
	m->repairing.state = new QState(this);
	m->repairing.state->setObjectName("repairing");
	m->repairing.state->assignProperty(this, "status", tr("Repairing"));

	emit repairingStateChanged();
}

void ServiceStateMachine::resetEvacuatingState()
{
	clearState(m->evacuating.state);
	m->evacuating.state = new QState(this);
	m->evacuating.state->setObjectName("evacuating");
	m->evacuating.state->assignProperty(this, "status", tr("Evacuating"));

	emit evacuatingStateChanged();
}

void ServiceStateMachine::resetInterruptedState()
{
	clearState(m->interrupted.state);
	m->interrupted.state = new QState(this);
	m->interrupted.state->setObjectName("interrupted");
	m->interrupted.state->assignProperty(this, "status", tr("Interrupted"));

	emit interruptedStateChanged();
}

void ServiceStateMachine::setUpStopped(bool reconfigure)
{
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(m->evacuating, 0);
		clearTransition(m->stopping, 0);
		clearTransition(m->stopped, 0);

		// (Re)create the state.
		resetStoppedState();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addEvacuatingTransition(0);
		addStoppingTransition(0);
	}
	// Outgoing transitions.
	addStoppedTransition(0);

	// Notify if this state was entered.
	connect(stoppedState(), & QState::entered, this, [this]() {
		if (m->lastNotifiableState != stoppedState())
			Notification::Info(tr("Service '%1' is stopped.").arg(m->service->name()));
		m->lastNotifiableState = stoppedState();
	});

	// Set this state as initial state.
	setInitialState(stoppedState());
}

void ServiceStateMachine::setUpStarting(bool reconfigure)
{
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(m->stopped, 0);
		clearTransition(m->starting, 0);
		clearTransition(m->starting, 1);
		clearTransition(m->starting, 2);

		// (Re)create the state.
		resetStartingState();
	}

	// Configure timeout.
	connect(startingState(), & QState::entered, this, [this]() {
		if (m->service->startTimeout() >= 0)
			m->timeoutTimer.start(m->service->startTimeout());
	});
	// It's safer to stop timeout, so that it won't make a false shot.
	connect(startingState(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addStoppedTransition(0);
	}
	// Outgoing transitions.
	addStartingTransition(0);
	addStartingTransition(1);
	addStartingTransition(2);

	// Allow servicable to configure this state.
	m->serviceable->configureStarting(startingState(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});
}

void ServiceStateMachine::setUpStarted(bool reconfigure)
{
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(m->starting, 0);
		clearTransition(m->repairing, 0);
		clearTransition(m->started, 0);
		clearTransition(m->started, 1);
		// Started substate transitions will be deleted along with Started state object.

		// (Re)create the state.
		resetStartedState();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addStartedTransition(0);
		addRepairingTransition(0);
	}
	// Outgoing transitions.
	addStartedTransition(0);
	addStartedTransition(1);
	// Started sub-state transitions.
	startedState()->addYieldingTransition(0);
	startedState()->addActiveTransition(0);
	startedState()->addIdlingTransition(0);

	// Allow servicable to configure this state.
	m->serviceable->configureStarted(startedState()->activeState(), startedState()->idlingState(), startedState()->yieldingState(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});

	// Notify if this state was entered.
	connect(startedState(), & QState::entered, this, [this]() {
		if (m->lastNotifiableState != startedState())
			Notification::Info(tr("Service '%1' has started.").arg(m->service->name()));
		m->lastNotifiableState = startedState();
	});
}

void ServiceStateMachine::setUpStopping(bool reconfigure)
{
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(m->started, 0);
		clearTransition(m->stopping, 0);
		clearTransition(m->stopping, 1);

		// (Re)create the state.
		resetStoppingState();
	}

	// Configure timeout.
	connect(stoppingState(), & QState::entered, this, [this]() {
		if (m->service->stopTimeout() >= 0)
			m->timeoutTimer.start(m->service->stopTimeout());
	});
	// It's safer to stop timeout, so that it won't make a false shot.
	connect(stoppingState(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addStartedTransition(0);
	}
	// Outgoing transitions.
	addStoppingTransition(0);
	addStoppingTransition(1);

	// Allow servicable to configure this state.
	m->serviceable->configureStopping(stoppingState(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});
}

void ServiceStateMachine::setUpBroken(bool reconfigure)
{
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(m->started, 1);
		clearTransition(m->starting, 1);
		clearTransition(m->starting, 2);
		clearTransition(m->repairing, 1);
		clearTransition(m->repairing, 2);
		clearTransition(m->broken, 0);
		clearTransition(m->broken, 1);

		// (Re)create the state.
		resetBrokenState();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addStartedTransition(1);
		addStartingTransition(1);
		addStartingTransition(2);
		addRepairingTransition(1);
		addRepairingTransition(2);
	}
	// Outgoing transitions.
	addBrokenTransition(0);
	addBrokenTransition(1);

	// Allow servicable to configure this state.
	m->serviceable->configureBroken(brokenState(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});

	// Notify if this state was entered.
	connect(brokenState(), & QState::entered, this, [this]() {
		if (m->lastNotifiableState != brokenState())
			Notification::Critical(tr("Service '%1' broke.").arg(m->service->name()));
		m->lastNotifiableState = brokenState();
	});
}

void ServiceStateMachine::setUpRepairing(bool reconfigure)
{
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(m->broken, 0);
		clearTransition(m->repairing, 0);
		clearTransition(m->repairing, 1);
		clearTransition(m->repairing, 2);

		// (Re)create the state.
		resetRepairingState();
	}

	// Configure timeout.
	connect(repairingState(), & QState::entered, this, [this]() {
		if (m->service->repairTimeout() >= 0)
			m->timeoutTimer.start(m->service->repairTimeout());
	});
	// It's safer to stop timeout, so that it won't make false shot.
	connect(repairingState(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addBrokenTransition(0);
	}
	// Outgoing transitions.
	addRepairingTransition(0);
	addRepairingTransition(1);
	addRepairingTransition(2);

	// Allow servicable to configure this state.
	m->serviceable->configureRepairing(repairingState(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});
}

void ServiceStateMachine::setUpEvacuating(bool reconfigure)
{
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(m->broken, 1);
		clearTransition(m->evacuating, 0);
		clearTransition(m->evacuating, 1);

		// (Re)create the state.
		resetEvacuatingState();
	}

	// Configure timeout.
	connect(evacuatingState(), & QState::entered, this, [this]() {
		if (m->service->stopTimeout() >= 0)
			m->timeoutTimer.start(m->service->stopTimeout());
	});
	// It's safer to stop timeout, so that it won't make false shot.
	connect(evacuatingState(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addBrokenTransition(1);
	}
	// Outgoing transitions.
	addEvacuatingTransition(0);
	addEvacuatingTransition(1);

	// Allow servicable to configure this state.
	m->serviceable->configureEvacuating(evacuatingState(), [this](QState & state, const QString & status) {
		state.assignProperty(this, "status", status);
	});
}

void ServiceStateMachine::setUpInterrupted(bool reconfigure)
{
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(m->evacuating, 1);
		clearTransition(m->stopping, 1);

		// (Re)create the state.
		resetInterruptedState();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addEvacuatingTransition(1);
		addStoppingTransition(1);
	}
	// Outgoing transitions.
	// None.

	// Notify if this state was entered.
	connect(interruptedState(), & QState::entered, this, [this]() {
		if (m->lastNotifiableState != interruptedState())
			Notification::Critical(tr("Stop sequence of '%1' service has been interrupted, because it took more than %2 [ms] to stop the service.").arg(m->service->name()).arg(m->service->stopTimeout()));
		m->lastNotifiableState = interruptedState();
	});
}

void ServiceStateMachine::addStoppedTransition(int index)
{
	auto state = stoppedState();

	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			stoppedTransition(index) = state->addTransition(m->service, & AbstractService::started, startingState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void ServiceStateMachine::addStartingTransition(int index)
{
	auto state = startingState();

	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			startingTransition(index) = addServiceableTransition(state, startedState(), m->serviceable->transitionToStarted(), true);
			break;
		case 1:
			startingTransition(index) = addServiceableTransition(state, brokenState(), m->serviceable->transitionToBroken());
			break;
		case 2:
			startingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, brokenState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}

}

void ServiceStateMachine::addStartedTransition(int index)
{
	auto state = startedState();

	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			startedTransition(index) = state->addTransition(m->service, & AbstractService::stopped, stoppingState());
			break;
		case 1:
			startedTransition(index) = addServiceableTransition(state, brokenState(), m->serviceable->transitionToBroken());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void ServiceStateMachine::addStoppingTransition(int index)
{
	auto state = stoppingState();

	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			stoppingTransition(index) = addServiceableTransition(state, stoppedState(), m->serviceable->transitionToStopped(), true);
			break;
		case 1:
			stoppingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, interruptedState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void ServiceStateMachine::addBrokenTransition(int index)
{
	auto state = brokenState();

	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			brokenTransition(index) = state->addTransition(m->service, & AbstractService::started, repairingState());
			break;
		case 1:
			brokenTransition(index) = state->addTransition(m->service, & AbstractService::stopped, evacuatingState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void ServiceStateMachine::addRepairingTransition(int index)
{
	auto state = repairingState();

	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			repairingTransition(index) = addServiceableTransition(state, startedState(), m->serviceable->transitionToStarted(), true);
			break;
		case 1:
			repairingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, brokenState());
			break;
		case 2:
			repairingTransition(index) = addServiceableTransition(state, brokenState(), m->serviceable->transitionToBroken());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void ServiceStateMachine::addEvacuatingTransition(int index)
{
	auto state = evacuatingState();

	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			evacuatingTransition(index) = addServiceableTransition(state, stoppedState(), m->serviceable->transitionToStopped(), true);
			break;
		case 1:
			evacuatingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, interruptedState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void ServiceStateMachine::addInterrputedTransition(int index)
{
	auto state = interruptedState();

	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr");
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void ServiceStateMachine::clearState(QState * state)
{
	if (state != nullptr) {
		removeState(state);
		state->deleteLater();
	}
}

ServiceStateMachine::StartedState::StartedState(ServiceStateMachine * parent):
	QState(parent),
	m(new Members{
	{ new QState(this), {} },
	{ new QState(this), {} },
	{ new QState(this), {} }})
{
	setInitialState(m->yielding.state);

	m->yielding.state->setObjectName("started.yielding");
	m->active.state->setObjectName("started.active");
	m->idling.state->setObjectName("started.idling");
}

QState * ServiceStateMachine::StartedState::idlingState()
{
	return m->idling.state;
}

const QState * ServiceStateMachine::StartedState::idlingState() const
{
	return m->idling.state;
}

QState * ServiceStateMachine::StartedState::yieldingState()
{
	return m->yielding.state;
}

const QState * ServiceStateMachine::StartedState::yieldingState() const
{
	return m->yielding.state;
}

QState * ServiceStateMachine::StartedState::activeState()
{
	return m->active.state;
}

const QState * ServiceStateMachine::StartedState::activeState() const
{
	return m->active.state;
}

QAbstractTransition *& ServiceStateMachine::StartedState::yieldingTransition(int index)
{
	return m->yielding.transitions[index];
}

QAbstractTransition * const & ServiceStateMachine::StartedState::yieldingTransition(int index) const
{
	return m->yielding.transitions[index];
}

QAbstractTransition *& ServiceStateMachine::StartedState::activeTransition(int index)
{
	return m->active.transitions[index];
}

QAbstractTransition * const & ServiceStateMachine::StartedState::activeTransition(int index) const
{
	return m->active.transitions[index];
}

QAbstractTransition *& ServiceStateMachine::StartedState::idlingTransition(int index)
{
	return m->idling.transitions[index];
}

QAbstractTransition * const & ServiceStateMachine::StartedState::idlingTransition(int index) const
{
	return m->idling.transitions[index];
}

QAbstractState * ServiceStateMachine::StartedState::state(int index)
{
	switch (index) {
		case YIELDING_STATE:
			return m->yielding.state;
		case ACTIVE_STATE:
			return m->active.state;
		case IDLING_STATE:
			return m->idling.state;
		default:
			CUTEHMI_WARNING("No state is associated with index " << index << " within '" << objectName() << "' state.");
	}

	return nullptr;
}

QAbstractTransition * ServiceStateMachine::StartedState::transition(int stateIndex, int transitionIndex)
{
	switch (stateIndex) {
		case YIELDING_STATE:
			return getTransition(m->yielding.transitions, transitionIndex);
		case ACTIVE_STATE:
			return getTransition(m->active.transitions, transitionIndex);
		case IDLING_STATE:
			return getTransition(m->idling.transitions, transitionIndex);
		default:
			CUTEHMI_WARNING("No state is associated with index " << stateIndex << " within '" << objectName() << "' state.");
	}

	return nullptr;
}

void ServiceStateMachine::StartedState::replaceTransitionToIdling()
{
	clearTransition(m->active, 0);

	addActiveTransition(0);
}

void ServiceStateMachine::StartedState::replaceTransitionToYielding()
{
	clearTransition(m->idling, 0);

	addIdlingTransition(0);
}

void ServiceStateMachine::StartedState::addYieldingTransition(int index)
{
	auto state = yieldingState();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			yieldingTransition(index) = state->addTransition(serviceStateMachine()->service(), & AbstractService::activated, activeState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void ServiceStateMachine::StartedState::addIdlingTransition(int index)
{
	CUTEHMI_ASSERT(serviceStateMachine() != nullptr, "serviceableStateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(serviceStateMachine()->serviceable() != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		case 0:
			idlingTransition(0) = addServiceableTransition(idlingState(), yieldingState(), serviceStateMachine()->serviceable()->transitionToYielding(), true);
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void ServiceStateMachine::StartedState::addActiveTransition(int index)
{
	CUTEHMI_ASSERT(serviceStateMachine() != nullptr, "serviceableStateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(serviceStateMachine()->serviceable() != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		case 0:
			activeTransition(0) = addServiceableTransition(activeState(), idlingState(), serviceStateMachine()->serviceable()->transitionToIdling());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

ServiceStateMachine * ServiceStateMachine::StartedState::serviceStateMachine() const
{
	return static_cast<ServiceStateMachine *>(parent());
}

}
}
}
