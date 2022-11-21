#include "ServiceStateInterface.hpp"
#include "ServiceStateMachine.hpp"

namespace cutehmi {
namespace services {
namespace internal {

ServiceStateInterface::ServiceStateInterface():
	m(new Members{
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	std::make_unique<QState>(),
	nullptr})
{
	m->dummyStopped->setObjectName("stopped");
	m->dummyStarting->setObjectName("starting");
	m->dummyStarted->setObjectName("started");
	m->dummyStopping->setObjectName("stopping");
	m->dummyBroken->setObjectName("broken");
	m->dummyRepairing->setObjectName("repairing");
	m->dummyEvacuating->setObjectName("evacuating");
	m->dummyInterrupted->setObjectName("interrupted");
	m->dummyStartedYielding->setObjectName("started.yielding");
	m->dummyStartedActive->setObjectName("started.active");
	m->dummyStartedIdling->setObjectName("started.idling");

	setDummyStates();
}

void ServiceStateInterface::bindStateMachine(ServiceStateMachine * serviceStateMachine)
{
	m->serviceStateMachine = serviceStateMachine;

	smSetStopped();
	smSetStarting();
	smSetStarted();
	smSetStopping();
	smSetBroken();
	smSetRepairing();
	smSetEvacuating();
	smSetInterrupted();

	connect(serviceStateMachine, & ServiceStateMachine::stoppedStateChanged, this, & ServiceStateInterface::smSetStopped);
	connect(serviceStateMachine, & ServiceStateMachine::startingStateChanged, this, & ServiceStateInterface::smSetStarting);
	connect(serviceStateMachine, & ServiceStateMachine::startedStateAndSubstatesChanged, this, & ServiceStateInterface::smSetStarted);
	connect(serviceStateMachine, & ServiceStateMachine::stoppingStateChanged, this, & ServiceStateInterface::smSetStopping);
	connect(serviceStateMachine, & ServiceStateMachine::brokenStateChanged, this, & ServiceStateInterface::smSetBroken);
	connect(serviceStateMachine, & ServiceStateMachine::repairingStateChanged, this, & ServiceStateInterface::smSetRepairing);
	connect(serviceStateMachine, & ServiceStateMachine::evacuatingStateChanged, this, & ServiceStateInterface::smSetEvacuating);
	connect(serviceStateMachine, & ServiceStateMachine::interruptedStateChanged, this, & ServiceStateInterface::smSetInterrupted);
}

void ServiceStateInterface::unbindStateMachine()
{
	m->serviceStateMachine->disconnect(this);
	m->serviceStateMachine = nullptr;

	setDummyStates();
}

void ServiceStateInterface::smSetStopped()
{
	setStopped(m->serviceStateMachine->stoppedState());
}

void ServiceStateInterface::smSetStarting()
{
	setStarting(m->serviceStateMachine->startingState());
}

void ServiceStateInterface::smSetStarted()
{
	setStarted(m->serviceStateMachine->startedState(),
			m->serviceStateMachine->startedState()->yieldingState(),
			m->serviceStateMachine->startedState()->activeState(),
			m->serviceStateMachine->startedState()->idlingState());
}

void ServiceStateInterface::smSetStopping()
{
	setStopping(m->serviceStateMachine->stoppingState());
}

void ServiceStateInterface::smSetBroken()
{
	setBroken(m->serviceStateMachine->brokenState());
}

void ServiceStateInterface::smSetRepairing()
{
	setRepairing(m->serviceStateMachine->repairingState());
}

void ServiceStateInterface::smSetEvacuating()
{
	setEvacuating(m->serviceStateMachine->evacuatingState());
}

void ServiceStateInterface::smSetInterrupted()
{
	setInterrupted(m->serviceStateMachine->interruptedState());
}

void ServiceStateInterface::setDummyStates()
{
	setStopped(m->dummyStopped.get());
	setStarting(m->dummyStarting.get());
	setStarted(m->dummyStarted.get(),
			m->dummyStartedYielding.get(),
			m->dummyStartedActive.get(),
			m->dummyStartedIdling.get());
	setStopping(m->dummyStopping.get());
	setBroken(m->dummyBroken.get());
	setRepairing(m->dummyRepairing.get());
	setEvacuating(m->dummyEvacuating.get());
	setInterrupted(m->dummyInterrupted.get());
}

}
}
}
