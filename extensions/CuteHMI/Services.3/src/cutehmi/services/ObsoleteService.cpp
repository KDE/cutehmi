#include <cutehmi/services/Service.hpp>

#include <cutehmi/services/ServiceManager.hpp>
#include <cutehmi/Notification.hpp>
#include <cutehmi/services/internal/ServiceStateMachine.hpp>

#include <QCoreApplication>

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
	setStatus(DefaultStatus());
}

Service::~Service()
{
	// Stop the service.
	stop();

	if (m->stateMachine) {
		// Wait till either service stops or it is interrupted.
		while (!m->stateMachine->stoppedState()->active() && !m->stateMachine->interruptedState()->active()) {
			// Due to repair and start timeouts service may end up in broken state. Try to stop the service repeatedly.
			stop();

			// QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents) slows down shutdown, so execute this loop aggressively.
			QCoreApplication::processEvents();
		}

		m->stateMachine->stop();
	}
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
		destroyStateMachine();
		m->serviceable = serviceablePtr;
		if (m->serviceable) {
			if (!m->deferStateMachineInitialization)
				initializeStateMachine();
		} else
			setStatus(DefaultStatus());

		emit serviceableChanged();
	}
}

QVariant Service::serviceable() const
{
	return QVariant::fromValue(m->serviceable);
}

void Service::classBegin()
{
	m->deferStateMachineInitialization = true;
}

void cutehmi::services::Service::componentComplete()
{
	if (m->deferStateMachineInitialization && m->serviceable)
		initializeStateMachine();

	m->deferStateMachineInitialization = false;
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

void Service::activate()
{
	emit activated();
}

internal::StateInterface * Service::stateInterface()
{
	return m->stateInterface;
}

const internal::StateInterface * Service::stateInterface() const
{
	return m->stateInterface;
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
	static QString name = QObject::tr("No serviceable");
	return name;
}

void Service::resetStopped(bool reconfigure)
{
	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	auto sm = m->stateMachine;

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(sm->evacuatingState(), sm->evacuatingTransition(0));
		clearTransition(sm->stoppingState(), sm->stoppingTransition(0));
		clearTransition(sm->stoppedState(), sm->stoppedTransition(0));

		// (Re)create the state.
		sm->recreateStoppedState();
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
}

void Service::resetStarting(bool reconfigure)
{
	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	auto sm = m->stateMachine;

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(sm->stoppedState(), sm->stoppedTransition(0));
		clearTransition(sm->startingState(), sm->startingTransition(0));
		clearTransition(sm->startingState(), sm->startingTransition(1));
		clearTransition(sm->startingState(), sm->startingTransition(2));

		// (Re)create the state.
		sm->recreateStartingState();
	}

	// Configure timeout.
	connect(sm->startingState(), & QState::entered, this, [this]() {
		if (startTimeout() >= 0)
			m->timeoutTimer.start(startTimeout());
	});
	// It's safer to stop timeout, so that it won't make a false shot.
	connect(sm->startingState(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

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
	m->serviceable->configureStarting(sm->startingState(), [this](QState & state, const QString & status) {
		state.assignProperty(m->stateMachine, "status", status);
	});
}

void Service::resetStarted(bool reconfigure)
{
	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	auto sm = m->stateMachine;

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(sm->startingState(), sm->startingTransition(0));
		clearTransition(sm->repairingState(), sm->repairingTransition(0));
		clearTransition(sm->startedState(), sm->startedTransition(0));
		clearTransition(sm->startedState(), sm->startedTransition(1));
		// Started substate transitions will be deleted along with Started state object.

		// (Re)create the state.
		sm->recreateStartedState();
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
	sm->startedState()->yieldingTransition(0) = sm->startedState()->yieldingState()->addTransition(this, & Service::activated, sm->startedState()->activeState());
	sm->startedState()->activeTransition(0) = addServiceableTransition(sm->startedState()->activeState(), sm->startedState()->idlingState(), m->serviceable->transitionToIdling());
	sm->startedState()->idlingTransition(0) = addServiceableTransition(sm->startedState()->idlingState(), sm->startedState()->yieldingState(), m->serviceable->transitionToYielding(), true);

	// Allow servicable to configure this state.
	m->serviceable->configureStarted(sm->startedState()->activeState(), sm->startedState()->idlingState(), sm->startedState()->yieldingState(), [this](QState & state, const QString & status) {
		state.assignProperty(m->stateMachine, "status", status);
	});
}

void Service::resetStopping(bool reconfigure)
{
	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	auto sm = m->stateMachine;

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(sm->startedState(), sm->startedTransition(0));
		clearTransition(sm->stoppingState(), sm->stoppingTransition(0));
		clearTransition(sm->stoppingState(), sm->stoppingTransition(1));

		// (Re)create the state.
		sm->recreateStoppingState();
	}

	// Configure timeout.
	connect(sm->stoppingState(), & QState::entered, this, [this]() {
		if (stopTimeout() >= 0)
			m->timeoutTimer.start(stopTimeout());
	});
	// It's safer to stop timeout, so that it won't make a false shot.
	connect(sm->stoppingState(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

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
	m->serviceable->configureStopping(sm->stoppingState(), [this](QState & state, const QString & status) {
		state.assignProperty(m->stateMachine, "status", status);
	});
}

void Service::resetBroken(bool reconfigure)
{
	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	auto sm = m->stateMachine;

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(sm->startedState(), sm->startedTransition(1));
		clearTransition(sm->startingState(), sm->startingTransition(1));
		clearTransition(sm->startingState(), sm->startingTransition(2));
		clearTransition(sm->repairingState(), sm->repairingTransition(1));
		clearTransition(sm->repairingState(), sm->repairingTransition(2));
		clearTransition(sm->brokenState(), sm->brokenTransition(0));
		clearTransition(sm->brokenState(), sm->brokenTransition(1));

		// (Re)create the state.
		sm->recreateBrokenState();
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
	m->serviceable->configureBroken(sm->brokenState(), [this](QState & state, const QString & status) {
		state.assignProperty(m->stateMachine, "status", status);
	});
}

void Service::resetRepairing(bool reconfigure)
{
	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	auto sm = m->stateMachine;

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(sm->brokenState(), sm->brokenTransition(0));
		clearTransition(sm->repairingState(), sm->repairingTransition(0));
		clearTransition(sm->repairingState(), sm->repairingTransition(1));
		clearTransition(sm->repairingState(), sm->repairingTransition(2));

		// (Re)create the state.
		sm->recreateRepairingState();
	}

	// Configure timeout.
	connect(sm->repairingState(), & QState::entered, this, [this]() {
		if (repairTimeout() >= 0)
			m->timeoutTimer.start(repairTimeout());
	});
	// It's safer to stop timeout, so that it won't make false shot.
	connect(sm->repairingState(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

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
	m->serviceable->configureBroken(sm->repairingState(), [this](QState & state, const QString & status) {
		state.assignProperty(m->stateMachine, "status", status);
	});
}

void Service::resetEvacuating(bool reconfigure)
{
	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	auto sm = m->stateMachine;

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(sm->brokenState(), sm->brokenTransition(1));
		clearTransition(sm->evacuatingState(), sm->evacuatingTransition(0));
		clearTransition(sm->evacuatingState(), sm->evacuatingTransition(1));

		// (Re)create the state.
		sm->recreateEvacuatingState();
	}

	// Configure timeout.
	connect(sm->evacuatingState(), & QState::entered, this, [this]() {
		if (stopTimeout() >= 0)
			m->timeoutTimer.start(stopTimeout());
	});
	// It's safer to stop timeout, so that it won't make false shot.
	connect(sm->evacuatingState(), & QState::exited, & m->timeoutTimer, & QTimer::stop);

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
	m->serviceable->configureEvacuating(sm->evacuatingState(), [this](QState & state, const QString & status) {
		state.assignProperty(m->stateMachine, "status", status);
	});
}

void Service::resetInterrupted(bool reconfigure)
{
	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);

	auto sm = m->stateMachine;

	if (reconfigure) {
		// Remove and delete old transitions (incomming and outgoing).
		clearTransition(sm->evacuatingState(), sm->evacuatingTransition(1));
		clearTransition(sm->stoppingState(), sm->stoppingTransition(1));

		// (Re)create the state.
		sm->recreateInterruptedState();
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
}

void Service::addStoppedTransition(int index)
{
	auto sm = m->stateMachine;
	auto state = sm->stoppedState();

	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		case 0:
			sm->stoppedTransition(index) = state->addTransition(this, & Service::started, sm->startingState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void Service::addStartingTransition(int index)
{
	auto sm = m->stateMachine;
	auto state = sm->startingState();

	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		case 0:
			sm->startingTransition(index) = addServiceableTransition(state, sm->startedState(), m->serviceable->transitionToStarted(), true);
			break;
		case 1:
			sm->startingTransition(index) = addServiceableTransition(state, sm->brokenState(), m->serviceable->transitionToBroken());
			break;
		case 2:
			sm->startingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, sm->brokenState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}

}

void Service::addStartedTransition(int index)
{
	auto sm = m->stateMachine;
	auto state = sm->startedState();

	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		case 0:
			sm->startedTransition(index) = state->addTransition(this, & Service::stopped, sm->stoppingState());
			break;
		case 1:
			sm->startedTransition(index) = addServiceableTransition(state, sm->brokenState(), m->serviceable->transitionToBroken());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void Service::addStoppingTransition(int index)
{
	auto sm = m->stateMachine;
	auto state = sm->stoppingState();

	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		case 0:
			sm->stoppingTransition(index) = addServiceableTransition(state, sm->stoppedState(), m->serviceable->transitionToStopped(), true);
			break;
		case 1:
			sm->stoppingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, sm->interruptedState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void Service::addBrokenTransition(int index)
{
	auto sm = m->stateMachine;
	auto state = sm->brokenState();

	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		case 0:
			sm->brokenTransition(index) = state->addTransition(this, & Service::started, sm->repairingState());
			break;
		case 1:
			sm->brokenTransition(index) = state->addTransition(this, & Service::stopped, sm->evacuatingState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void Service::addRepairingTransition(int index)
{
	auto sm = m->stateMachine;
	auto state = sm->repairingState();

	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		case 0:
			sm->repairingTransition(index) = addServiceableTransition(state, sm->startedState(), m->serviceable->transitionToStarted(), true);
			break;
		case 1:
			sm->repairingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, sm->brokenState());
			break;
		case 2:
			sm->repairingTransition(index) = addServiceableTransition(state, sm->brokenState(), m->serviceable->transitionToBroken());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void Service::addEvacuatingTransition(int index)
{
	auto sm = m->stateMachine;
	auto state = sm->evacuatingState();

	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		case 0:
			sm->evacuatingTransition(index) = addServiceableTransition(state, sm->stoppedState(), m->serviceable->transitionToStopped(), true);
			break;
		case 1:
			sm->evacuatingTransition(index) = state->addTransition(& m->timeoutTimer, & QTimer::timeout, sm->interruptedState());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void Service::addInterrputedTransition(int index)
{
	auto sm = m->stateMachine;
	auto state = sm->interruptedState();

	CUTEHMI_ASSERT(m->stateMachine != nullptr, "stateMachine can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(m->serviceable != nullptr, "serviceable can not be nullptr when calling " Q_FUNC_INFO);
	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr when calling " Q_FUNC_INFO);

	switch (index) {
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " Q_FUNC_INFO " function.");
	}
}

void Service::initializeDeprecatedStateMachine(Serviceable & serviceable)
{
	try {
		m->deprecatedStateMachine = new QStateMachine(this);
		m->stateInterface = new internal::StateInterface(m->deprecatedStateMachine);

		connect(m->stateInterface, & internal::StateInterface::statusChanged, this, [this]() {
			setStatus(m->stateInterface->status());
		});

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
		// It's safer to stop the timeout, so that it won't make false shot.
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


		m->deprecatedStateMachine->addState(& m->stateInterface->stopped());
		m->deprecatedStateMachine->addState(& m->stateInterface->interrupted());
		m->deprecatedStateMachine->addState(& m->stateInterface->starting());
		m->deprecatedStateMachine->addState(& m->stateInterface->started());
		m->deprecatedStateMachine->addState(& m->stateInterface->stopping());
		m->deprecatedStateMachine->addState(& m->stateInterface->broken());
		m->deprecatedStateMachine->addState(& m->stateInterface->repairing());
		m->deprecatedStateMachine->addState(& m->stateInterface->evacuating());
		m->deprecatedStateMachine->setInitialState(& m->stateInterface->stopped());


		m->stateInterface->stopped().addTransition(this, & Service::started, & m->stateInterface->starting());
		m->stateInterface->started().addTransition(this, & Service::stopped, & m->stateInterface->stopping());
		m->stateInterface->broken().addTransition(this, & Service::started, & m->stateInterface->repairing());
		m->stateInterface->broken().addTransition(this, & Service::stopped, & m->stateInterface->evacuating());
		m->stateInterface->stopping().addTransition(& m->timeoutTimer, & QTimer::timeout, & m->stateInterface->interrupted());
		m->stateInterface->starting().addTransition(& m->timeoutTimer, & QTimer::timeout, & m->stateInterface->broken());
		m->stateInterface->repairing().addTransition(& m->timeoutTimer, & QTimer::timeout, & m->stateInterface->broken());
		m->stateInterface->yielding().addTransition(this, & Service::activated, & m->stateInterface->active());
		m->stateInterface->evacuating().addTransition(& m->timeoutTimer, & QTimer::timeout, & m->stateInterface->interrupted());

//		const QMetaObject * metaObject = serviceable.transitionSignaller()->metaObject();
//		for (int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i) {
//			CUTEHMI_DEBUG(QMetaObject::normalizedSignature(metaObject->method(i).methodSignature()));
//			CUTEHMI_DEBUG(" is signal: " << (metaObject->method(i).methodType() == QMetaMethod::Signal));
//		}

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


//		serviceable.configureStarting(& m->stateInterface->starting(), [this](QState & state, const QString & status) {
//			if (m->stateInterface != nullptr)
//				state.assignProperty(m->stateInterface, "status", status);
//		});
//		serviceable.configureStarted(& m->stateInterface->active(), & m->stateInterface->idling(), & m->stateInterface->yielding(), [this](QState & state, const QString & status) {
//			if (m->stateInterface != nullptr)
//				state.assignProperty(m->stateInterface, "status", status);
//		});
//		serviceable.configureStopping(& m->stateInterface->stopping(), [this](QState & state, const QString & status) {
//			if (m->stateInterface != nullptr)
//				state.assignProperty(m->stateInterface, "status", status);
//		});
//		serviceable.configureBroken(& m->stateInterface->broken(), [this](QState & state, const QString & status) {
//			if (m->stateInterface != nullptr)
//				state.assignProperty(m->stateInterface, "status", status);
//		});
//		serviceable.configureRepairing(& m->stateInterface->repairing(), [this](QState & state, const QString & status) {
//			if (m->stateInterface != nullptr)
//				state.assignProperty(m->stateInterface, "status", status);
//		});
//		serviceable.configureEvacuating(& m->stateInterface->evacuating(), [this](QState & state, const QString & status) {
//			if (m->stateInterface != nullptr)
//				state.assignProperty(m->stateInterface, "status", status);
//		});

		m->deprecatedStateMachine->start();
		QCoreApplication::processEvents();	// This is required in order to truly start state machine and prevent it from ignoring incoming events.
	} catch (const std::exception & e) {
		CUTEHMI_CRITICAL("Could not initialize new state machine, because of following exception: " << e.what());
	}
}

void Service::initializeStateMachine()
{
	try {
		m->stateMachine = new internal::ServiceStateMachine(this);

		// Service status is read-only property, thus it is updated through state machine writebale double.
		connect(m->stateMachine, & internal::ServiceStateMachine::statusChanged, this, & Service::setStatus);

		// Variable m->lastNotifiableState is used to prevent notification spam, i.e. when service fails to leave notifiable state
		// through intermediate, non-notifiable state (e.g. 'broken' is a notifiable state, 'repairing' is an intermediate state;
		// without the condition "Service 'XYZ' broke" message would be posted after each failed repair attempt).
		connect(m->stateMachine->interruptedState(), & QState::entered, this, [this]() {
			if (m->lastNotifiableState != m->stateMachine->interruptedState())
				Notification::Critical(tr("Stop sequence of '%1' service has been interrupted, because it took more than %2 [ms] to stop the service.").arg(name()).arg(stopTimeout()));
			m->lastNotifiableState = m->stateMachine->interruptedState();
		});
		connect(m->stateMachine->startedState(), & QState::entered, this, [this]() {
			if (m->lastNotifiableState != m->stateMachine->startedState())
				Notification::Info(tr("Service '%1' has started.").arg(name()));
			m->lastNotifiableState = m->stateMachine->startedState();
		});
		connect(m->stateMachine->stoppedState(), & QState::entered, this, [this]() {
			if (m->lastNotifiableState != m->stateMachine->stoppedState())
				Notification::Info(tr("Service '%1' is stopped.").arg(name()));
			m->lastNotifiableState = m->stateMachine->stoppedState();
		});
		connect(m->stateMachine->brokenState(), & QState::entered, this, [this]() {
			if (m->lastNotifiableState != m->stateMachine->brokenState())
				Notification::Critical(tr("Service '%1' broke.").arg(name()));
			m->lastNotifiableState = m->stateMachine->brokenState();
		});

		resetStopped();
		resetStarting();
		resetStarted();
		resetStopping();
		resetBroken();
		resetRepairing();
		resetEvacuating();
		resetInterrupted();

		m->stateMachine->setInitialState(m->stateMachine->stoppedState());

		m->stateMachine->start();
		QCoreApplication::processEvents();	// This is required in order to truly start state machine and prevent it from ignoring incoming events.
	} catch (const std::exception & e) {
		CUTEHMI_CRITICAL("Could not initialize new state machine, because of following exception: " << e.what());
	}
}

void Service::destroyStateMachine()
{
	if (m->stateMachine) {
		m->stateMachine->stop();
		m->stateMachine->deleteLater();
		m->stateMachine = nullptr;
	}
}

void Service::addTransition(QState * source, QState * target, std::unique_ptr<QAbstractTransition> transition)
{
	///@todo remove - this is obsolete.
	if (transition) {
		transition->setParent(source);
		transition->setTargetState(target);
		source->addTransition(transition.release());
	} else
		source->addTransition(target);
}

QAbstractTransition * Service::addServiceableTransition(QState * source, QState * target, std::unique_ptr<QAbstractTransition> serviceableTransition, bool unconditionalIfNull)
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

void Service::clearTransition(QState * state, QAbstractTransition *& transition)
{
	if (transition != nullptr) {
		if (state != nullptr)
			state->removeTransition(transition);
		transition->deleteLater();
		transition = nullptr;
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
