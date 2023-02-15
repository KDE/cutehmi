#include "ServiceStartedStateInterface.hpp"
#include "ServiceStateMachine.hpp"
#include "ServiceStateInterface.hpp"
#include "stateInterfaceHelpers.hpp"
#include "AbstractService.hpp"

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

//(c)C: Copyright © 2022-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
