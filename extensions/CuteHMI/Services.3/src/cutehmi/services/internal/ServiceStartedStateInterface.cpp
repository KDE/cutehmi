#include "ServiceStartedStateInterface.hpp"
#include "ServiceStateMachine.hpp"
#include <cutehmi/services/AbstractService.hpp>

#include "ServiceStateInterface.hpp"
#include "stateInterfaceHelpers.hpp"

#include <QStateMachine>

namespace cutehmi {
namespace services {
namespace internal {

QAbstractState * ServiceStartedStateInterface::yielding() const
{
	return m->yielding.persistent;
}

QAbstractState * ServiceStartedStateInterface::active() const
{
	return m->active.persistent;
}

QAbstractState * ServiceStartedStateInterface::idling() const
{
	return m->idling.persistent;
}

ServiceStartedStateInterface::ServiceStartedStateInterface(ServiceStateInterface * parent, QState * started):
	StartedStateInterface(parent),
	m(new Members{
	{ new QState(started), nullptr, {} },
	{ new QState(started), nullptr, {} },
	{ new QState(started), nullptr, {} }})
{
	initializePersistentStates();
}

void ServiceStartedStateInterface::setStarted(QState * started)
{
	m->yielding.persistent->setParent(started);
	m->active.persistent->setParent(started);
	m->idling.persistent->setParent(started);
}

void ServiceStartedStateInterface::replaceTransitionToIdling(const Serviceable & serviceable)
{
	clearTransition(m->active, 0);

	addActiveTransition(0, serviceable);
}

void ServiceStartedStateInterface::replaceTransitionToYielding(const Serviceable & serviceable)
{
	clearTransition(m->idling, 0);

	addIdlingTransition(0, serviceable);
}

ServiceStateInterface * ServiceStartedStateInterface::stateInterface() const
{
	return static_cast<ServiceStateInterface *>(parent());
}

QState * ServiceStartedStateInterface::idlingPersistent() const
{
	return m->idling.persistent;
}

QState * ServiceStartedStateInterface::yieldingPersistent() const
{
	return m->yielding.persistent;
}

QState * ServiceStartedStateInterface::activePersistent() const
{
	return m->active.persistent;
}

QState * ServiceStartedStateInterface::idlingEphemeric() const
{
	return m->idling.ephemeric;
}

QState * ServiceStartedStateInterface::yieldingEphemeric() const
{
	return m->yielding.ephemeric;
}

QState * ServiceStartedStateInterface::activeEphemeric() const
{
	return m->active.ephemeric;
}

QAbstractTransition *& ServiceStartedStateInterface::yieldingTransition(int index)
{
	return m->yielding.transitions[index];
}

QAbstractTransition * const & ServiceStartedStateInterface::yieldingTransition(int index) const
{
	return m->yielding.transitions[index];
}

QAbstractTransition *& ServiceStartedStateInterface::activeTransition(int index)
{
	return m->active.transitions[index];
}

QAbstractTransition * const & ServiceStartedStateInterface::activeTransition(int index) const
{
	return m->active.transitions[index];
}

QAbstractTransition *& ServiceStartedStateInterface::idlingTransition(int index)
{
	return m->idling.transitions[index];
}

QAbstractTransition * const & ServiceStartedStateInterface::idlingTransition(int index) const
{
	return m->idling.transitions[index];
}

void ServiceStartedStateInterface::initializePersistentStates()
{
	m->yielding.persistent->setObjectName("started.yielding");
	m->yielding.persistent->assignProperty(stateInterface(), "status", tr("Yielding"));

	m->active.persistent->setObjectName("started.active");
	m->active.persistent->assignProperty(stateInterface(), "status", tr("Active"));

	m->idling.persistent->setObjectName("started.idling");
	m->idling.persistent->assignProperty(stateInterface(), "status", tr("Idling"));
}

void ServiceStartedStateInterface::resetEphemericStates()
{
	resetYieldingEphemeric();
	resetActiveEphemeric();
	resetIdlingEphemeric();
}

void ServiceStartedStateInterface::resetYieldingEphemeric()
{
	clearTransition(m->yielding, 0);

	recreateState(m->yielding, "started.yielding.ephemeric");
}

void ServiceStartedStateInterface::resetActiveEphemeric()
{
	clearTransition(m->active, 0);

	recreateState(m->active, "started.active.ephemeric");
}

void ServiceStartedStateInterface::resetIdlingEphemeric()
{
	clearTransition(m->idling, 0);

	recreateState(m->idling, "started.idling.ephemeric");
}

void ServiceStartedStateInterface::setUpYielding(bool reconfigure, const Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->idling, 0);

		// Reset the state.
		resetYieldingEphemeric();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addIdlingTransition(0, serviceable);
	}
	// Outgoing transitions.
	addYieldingTransition(0);
}

void ServiceStartedStateInterface::setUpActive(bool reconfigure, const Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->yielding, 0);

		// Reset the state.
		resetActiveEphemeric();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addYieldingTransition(0);
	}
	// Outgoing transitions.
	addActiveTransition(0, serviceable);
}

void ServiceStartedStateInterface::setUpIdling(bool reconfigure, const Serviceable & serviceable)
{
	if (reconfigure) {
		// Remove and delete old incomming transitions.
		clearTransition(m->active, 0);

		// Reset the state.
		resetIdlingEphemeric();
	}

	// To avoid states being added and removed during initial configuration let's introduce a convention that each state adds only
	// its outgoing transitions. When the sate is being reset later, upon reconfiure request, then all transitions involving this state
	// have to be readded and old transitions have to be deleted.

	if (reconfigure) {
		// Incomming transitions.
		addActiveTransition(0, serviceable);
	}
	// Outgoing transitions.
	addIdlingTransition(0, serviceable);
}

void ServiceStartedStateInterface::addYieldingTransition(int index)
{
	auto state = yieldingPersistent();

	CUTEHMI_ASSERT(state != nullptr, "state can not be nullptr");

	switch (index) {
		case 0:
			yieldingTransition(index) = state->addTransition(stateInterface()->service(), & AbstractService::activated, activePersistent());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
}

void ServiceStartedStateInterface::addIdlingTransition(int index, const Serviceable & serviceable)
{
	switch (index) {
		case 0:
			idlingTransition(0) = addServiceableTransition(idlingPersistent(), yieldingPersistent(), serviceable.transitionToYielding(), true);
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
}

void ServiceStartedStateInterface::addActiveTransition(int index, const Serviceable & serviceable)
{
	switch (index) {
		case 0:
			activeTransition(0) = addServiceableTransition(activePersistent(), idlingPersistent(), serviceable.transitionToIdling());
			break;
		default:
			CUTEHMI_CRITICAL("Transition with index " << index << " is not known to " << Q_FUNC_INFO << " function.");
	}
}

}
}
}
