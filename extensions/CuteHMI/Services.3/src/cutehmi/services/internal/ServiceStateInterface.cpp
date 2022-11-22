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
