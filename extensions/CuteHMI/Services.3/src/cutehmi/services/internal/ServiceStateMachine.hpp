#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_SRC_CUTEHMI_SERVICES_INTERNAL_SERVICESTATEMACHINE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_SRC_CUTEHMI_SERVICES_INTERNAL_SERVICESTATEMACHINE_HPP

#include <cutehmi/services/internal/common.hpp>

#include <QStateMachine>
#include <QTimer>

#include <array>

namespace cutehmi {
namespace services {

class AbstractService;
class Serviceable;

namespace internal {

/**
 * Service state machine.
 *
 * Service state machine defines state interface utilized by service and servicable objects.
 *
 * This class is intended to statisfy the needs of cutehmi::services::Service object.
 */
class CUTEHMI_SERVICES_PRIVATE ServiceStateMachine:
	public QStateMachine
{
		Q_OBJECT

	public:
		enum StateIndex : int {
			STOPPED_STATE = 0,
			STARTING_STATE = 1,
			STARTED_STATE = 2,
			STOPPING_STATE = 3,
			BROKEN_STATE = 4,
			REPAIRING_STATE = 5,
			EVACUATING_STATE = 6,
			INTERRUPTED_STATE = 7
		};

		class StartedState:
			public QState
		{
			public:
				enum StateIndex : int {
					YIELDING_STATE = 0,
					ACTIVE_STATE = 1,
					IDLING_STATE = 2
				};

				StartedState(ServiceStateMachine * parent);

				QState * idlingState();

				const QState * idlingState() const;

				QState * yieldingState();

				const QState * yieldingState() const;

				QState * activeState();

				const QState * activeState() const;

				QAbstractTransition *& yieldingTransition(int index);

				QAbstractTransition * const & yieldingTransition(int index) const;

				QAbstractTransition *& activeTransition(int index);

				QAbstractTransition * const & activeTransition(int index) const;

				QAbstractTransition *& idlingTransition(int index);

				QAbstractTransition * const & idlingTransition(int index) const;

				/**
				 * Get state by index. States are indexed according to [state interface diagram](../../../../dev/StandardStates.scxml).
				 * @param index state index.
				 * @return a state associated with the specified @a index or nullptr if no state is associated with given @a index.
				 *
				 * @see StateIndex enum.
				 */
				QAbstractState * state(int index);

				/**
				 * Get transition at specified state and transition indices.
				 *
				 * Transitions are indexed according to [state interface diagram](../../../../dev/StandardStates.scxml).
				 *
				 * @param stateIndex state index.
				 * @param transitionIndex transition index.
				 * @return transition object if it exists or @p nullptr otherwise. Additionaly a warning message is printed to the
				 * console if transition or state index is out of bounds.
				 */
				QAbstractTransition * transition(int stateIndex, int transitionIndex);

				void replaceTransitionToIdling();

				void replaceTransitionToYielding();

				void addYieldingTransition(int index);

				void addIdlingTransition(int index);

				void addActiveTransition(int index);

			private:
				ServiceStateMachine * serviceStateMachine() const;

				struct Members {
					struct {
						QState * state;
						std::array<QAbstractTransition *, 1> transitions;
					} idling;
					struct {
						QState * state;
						std::array<QAbstractTransition *, 1> transitions;
					} yielding;
					struct {
						QState * state;
						std::array<QAbstractTransition *, 1> transitions;
					} active;
				};

				MPtr<Members> m;
		};

		Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

		/**
		 * Constructor.
		 * @param service parent service object.
		 * @param serviceable serviceable object, which should be associated with @a service.
		 */
		ServiceStateMachine(AbstractService * service, Serviceable * serviceable);

		QString status() const;

		void setStatus(const QString & status);

		AbstractService * service() const;

		Serviceable * serviceable() const;

		QState * startingState();

		const QState * startingState() const;

		StartedState * startedState();

		const StartedState * startedState() const;

		QState * stoppingState();

		const QState * stoppingState() const;

		QState * stoppedState();

		const QState * stoppedState() const;

		QState * brokenState();

		const QState * brokenState() const;

		QState * repairingState();

		const QState * repairingState() const;

		QState * evacuatingState();

		const QState * evacuatingState() const;

		QState * interruptedState();

		const QState * interruptedState() const;

		QAbstractTransition *& startingTransition(int index);

		QAbstractTransition * const & startingTransition(int index) const;

		QAbstractTransition *& startedTransition(int index);

		QAbstractTransition * const & startedTransition(int index) const;

		QAbstractTransition *& stoppingTransition(int index);

		QAbstractTransition * const & stoppingTransition(int index) const;

		QAbstractTransition *& stoppedTransition(int index);

		QAbstractTransition * const & stoppedTransition(int index) const;

		QAbstractTransition *& brokenTransition(int index);

		QAbstractTransition * const & brokenTransition(int index) const;

		QAbstractTransition *& repairingTransition(int index);

		QAbstractTransition * const & repairingTransition(int index) const;

		QAbstractTransition *& evacuatingTransition(int index);

		QAbstractTransition * const & evacuatingTransition(int index) const;

		/**
		 * Find state with a specific name.
		 *
		 * State objects are given names with QObject::setObjectName() function. Particular state can be found by looking for an
		 * object with specified name in the state machine hierarchy. For major states names are straightforward:
		 * - "stopped"
		 * - "starting"
		 * - "started"
		 * - "stopping"
		 * - "broken"
		 * - "repairing"
		 * - "evacuating"
		 * - "interrupted"
		 * .
		 *
		 * To look for sub-states of the started state use dot separated name reflecting the inclusion relationship:
		 * - "started.yielding"
		 * - "started.active"
		 * - "started.idling"
		 * .
		 *
		 * @note although currently the name is assigned as is, in the future some level of indirection may be introduced - for
		 * example names of state objects may be given some prefix, so always use a function to find state object by its name.
		 *
		 * @param name name of the state to look for.
		 * @return a pointer to a state with given @a name, if it was found or @p nullptr otherwise.
		 */
		QAbstractState * findState(const QString & name);

		/**
		 * Get state by index. States are indexed according to [state interface diagram](../../../../dev/StandardStates.scxml).
		 * @param index state index.
		 * @return a state associated with the specified @a index or @p nullptr if no state is associated with given @a index.
		 * Additionaly a warning message is printed to the console if state index is out of bounds.
		 *
		 * @see StateIndex enum.
		 */
		QAbstractState * state(int index);

		/**
		 * Get transition at specified state and transition indices.
		 *
		 * Transitions are indexed according to [state interface diagram](../../../../dev/StandardStates.scxml).
		 *
		 * @param stateIndex state index.
		 * @param transitionIndex transition index.
		 * @return transition object if it exists or @p nullptr otherwise. Additionaly a warning message is printed to the
		 * console if transition or state index is out of bounds.
		 */
		QAbstractTransition * transition(int stateIndex, int transitionIndex);

		/**
		 * Start the state machine.
		 *
		 * This is shadowed function, which additionaly calls QCoreApplication::processEvents().
		 */
		void start();

		/**
		 * Perform service shutdown.
		 *
		 * This function executes a loop, which repeatedly calls QCoreApplication::processEvents() until the state machine ends up
		 * in stopped or interrupted state.
		 */
		void shutdown();

		void reconfigureStopped();

		void reconfigureStarting();

		void reconfigureStarted();

		void reconfigureStopping();

		void reconfigureBroken();

		void reconfigureRepairing();

		void reconfigureEvacuating();

		void reconfigureInterrupted();

		void replaceTransitionToStarted();

		void replaceTransitionToStopped();

		void replaceTransitionToBroken();

		void replaceTransitionToYielding();

		void replaceTransitionToIdling();

	signals:
		void statusChanged(const QString & status);

		void stoppedStateChanged();

		void startingStateChanged();

		void startedStateAndSubstatesChanged();

		void stoppingStateChanged();

		void brokenStateChanged();

		void repairingStateChanged();

		void evacuatingStateChanged();

		void interruptedStateChanged();

	private:
		void resetStartingState();

		void resetStartedState();

		void resetStoppingState();

		void resetStoppedState();

		void resetBrokenState();

		void resetRepairingState();

		void resetEvacuatingState();

		void resetInterruptedState();

		void setUpStopped(bool reconfigure);

		void setUpStarting(bool reconfigure);

		void setUpStarted(bool reconfigure);

		void setUpStopping(bool reconfigure);

		void setUpBroken(bool reconfigure);

		void setUpRepairing(bool reconfigure);

		void setUpEvacuating(bool reconfigure);

		void setUpInterrupted(bool reconfigure);

		/**
		 * Add outgoing transition to stopped state.
		 * @param index transition index.
		 */
		void addStoppedTransition(int index);

		/**
		 * Add outgoing transition to starting state.
		 * @param index transition index.
		 */
		void addStartingTransition(int index);

		/**
		 * Add outgoing transition to started state.
		 * @param index transition index.
		 */
		void addStartedTransition(int index);

		/**
		 * Add outgoing transition to stopping state.
		 * @param index transition index.
		 */
		void addStoppingTransition(int index);

		/**
		 * Add outgoing transition to broken state.
		 * @param index transition index.
		 */
		void addBrokenTransition(int index);

		/**
		 * Add outgoing transition to repairing state.
		 * @param index transition index.
		 */
		void addRepairingTransition(int index);

		/**
		 * Add outgoing transition to evacuating state.
		 * @param index transition index.
		 */
		void addEvacuatingTransition(int index);

		/**
		 * Add outgoing transition to interrupted state.
		 * @param index transition index.
		 */
		void addInterrputedTransition(int index);

		void clearState(QState * state);

		struct Members
		{
			AbstractService * service;
			Serviceable * serviceable;
			QTimer timeoutTimer;

			// Variable m->lastNotifiableState is used to prevent notification spam, i.e. when service fails to leave notifiable state
			// through intermediate, non-notifiable state (e.g. 'broken' is a notifiable state, 'repairing' is an intermediate state;
			// without the condition "Service 'XYZ' broke" message would be posted after each failed repair attempt).
			QState * lastNotifiableState = nullptr;

			struct {
				QState * state;
				std::array<QAbstractTransition *, 3> transitions;
			} starting;
			struct {
				StartedState * state;
				std::array<QAbstractTransition *, 2> transitions;
			} started;
			struct {
				QState * state;
				std::array<QAbstractTransition *, 2> transitions;
			} stopping;
			struct {
				QState * state;
				std::array<QAbstractTransition *, 1> transitions;
			} stopped;
			struct {
				QState * state;
				std::array<QAbstractTransition *, 2> transitions;
			} broken;
			struct {
				QState * state;
				std::array<QAbstractTransition *, 3> transitions;
			} repairing;
			struct {
				QState * state;
				std::array<QAbstractTransition *, 2> transitions;
			} evacuating;
			struct {
				QState * state;
				std::array<QAbstractTransition *, 0> transitions;
			} interrupted;
			QString status;
		};

		MPtr<Members> m;
};

}
}
}

#endif

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
