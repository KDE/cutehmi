#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_SRC_CUTEHMI_SERVICES_INTERNAL_SERVICESTATEINTERFACE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_SRC_CUTEHMI_SERVICES_INTERNAL_SERVICESTATEINTERFACE_HPP

#include "internal/common.hpp"
#include "StateInterface.hpp"
#include "ServiceStartedStateInterface.hpp"
#include "ServiceStateMachine.hpp"

#include <QState>
#include <QTimer>
#include <QStateMachine>

#include <memory>

namespace cutehmi {
namespace services {

class Serviceable;

namespace internal {

class CUTEHMI_SERVICES_PRIVATE ServiceStateInterface:
	public StateInterface
{
		Q_OBJECT

	public:
		Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

		ServiceStateInterface();

		~ServiceStateInterface() override;

		using StateInterface::service;

		QString status() const;

		void setStatus(const QString & status);

		bool isShutdown() const;

		ServiceStateMachine * stateMachine() const;

		void configureServiceable(Serviceable * serviceable);

		QAbstractState * stopped() const override;

		QAbstractState * starting() const override;

		QAbstractState * started() const override;

		QAbstractState * stopping() const override;

		QAbstractState * broken() const override;

		QAbstractState * repairing() const override;

		QAbstractState * evacuating() const override;

		QAbstractState * interrupted() const override;

		StartedStateInterface * startedStates() const override;

		void reconfigureStopped(const Serviceable & serviceable);

		void reconfigureStarting(Serviceable & serviceable);

		void reconfigureStarted(Serviceable & serviceable);

		void reconfigureStopping(Serviceable & serviceable);

		void reconfigureBroken(Serviceable & serviceable);

		void reconfigureRepairing(Serviceable & serviceable);

		void reconfigureEvacuating(Serviceable & serviceable);

		void reconfigureInterrupted(const Serviceable & serviceable);

		void replaceTransitionToStarted(const Serviceable & serviceable);

		void replaceTransitionToStopped(const Serviceable & serviceable);

		void replaceTransitionToBroken(const Serviceable & serviceable);

		void replaceTransitionToYielding(const Serviceable & serviceable);

		void replaceTransitionToIdling(const Serviceable & serviceable);

		/**
		 * Perform service shutdown.
		 *
		 * This function executes a loop, which repeatedly calls QCoreApplication::processEvents() until the state machine ends up
		 * in stopped or interrupted state.
		 *
		 * The service may end up in inconsistent state after getting killed. Non-const methods should not used after the shutdown.
		 * This also applies to return values of const methods.
		 */
		void shutdown();

	signals:
		void statusChanged(const QString & status);

	private:
		QState * startingPersistent() const;

		QState * startedPersistent() const;

		cutehmi::services::internal::ServiceStartedStateInterface * startedInterface() const;

		QState * stoppingPersistent() const;

		QState * stoppedPersistent() const;

		QState * brokenPersistent() const;

		QState * repairingPersistent() const;

		QState * evacuatingPersistent() const;

		QState * interruptedPersistent() const;

		QState * startingEphemeric() const;

		QState * startedEphemeric() const;

		QState * stoppingEphemeric() const;

		QState * stoppedEphemeric() const;

		QState * brokenEphemeric() const;

		QState * repairingEphemeric() const;

		QState * evacuatingEphemeric() const;

		QState * interruptedEphemeric() const;

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

		void initializePersistentStates();

		void resetEphemericStates();

		void resetStartingEphemeric();

		void resetStartedEphemeric();

		void resetStoppingEphemeric();

		void resetStoppedEphemeric();

		void resetBrokenEphemeric();

		void resetRepairingEphemeric();

		void resetEvacuatingEphemeric();

		void resetInterruptedEphemeric();

		void setUpStopped(bool reconfigure, const Serviceable & serviceable);

		void setUpStarting(bool reconfigure, Serviceable & serviceable);

		void setUpStarted(bool reconfigure, Serviceable & serviceable);

		void setUpStopping(bool reconfigure, Serviceable & serviceable);

		void setUpBroken(bool reconfigure, Serviceable & serviceable);

		void setUpRepairing(bool reconfigure, Serviceable & serviceable);

		void setUpEvacuating(bool reconfigure, Serviceable & serviceable);

		void setUpInterrupted(bool reconfigure, const Serviceable & serviceable);

		/**
		 * Add outgoing transition to stopped state.
		 * @param index transition index.
		 */
		void addStoppedTransition(int index);

		/**
		 * Add outgoing transition to starting state.
		 * @param index transition index.
		 * @param serviceable serviceable object.
		 */
		void addStartingTransition(int index, const Serviceable & serviceable);

		/**
		 * Add outgoing transition to started state.
		 * @param index transition index.
		 * @param serviceable serviceable object.
		 */
		void addStartedTransition(int index, const Serviceable & serviceable);

		/**
		 * Add outgoing transition to stopping state.
		 * @param index transition index.
		 * @param serviceable serviceable object.
		 */
		void addStoppingTransition(int index, const Serviceable & serviceable);

		/**
		 * Add outgoing transition to broken state.
		 * @param index transition index.
		 */
		void addBrokenTransition(int index);

		/**
		 * Add outgoing transition to repairing state.
		 * @param index transition index.
		 * @param serviceable serviceable object.
		 */
		void addRepairingTransition(int index, const Serviceable & serviceable);

		/**
		 * Add outgoing transition to evacuating state.
		 * @param index transition index.
		 * @param serviceable serviceable object.
		 */
		void addEvacuatingTransition(int index, const Serviceable & serviceable);

		/**
		 * Add outgoing transition to interrupted state.
		 * @param index transition index.
		 */
		void addInterrputedTransition(int index);

	private:
		struct Members {
			QTimer timeoutTimer;

			// Variable m->lastNotifiableState is used to prevent notification spam, i.e. when service fails to leave notifiable state
			// through intermediate, non-notifiable state (e.g. 'broken' is a notifiable state, 'repairing' is an intermediate state;
			// without the condition "Service 'XYZ' broke" message would be posted after each failed repair attempt).
			QState * lastNotifiableState = nullptr;

			ServiceStateMachine * stateMachine;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 3> transitions;
			} starting;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 2> transitions;
				ServiceStartedStateInterface * interface;
			} started;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 2> transitions;
			} stopping;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 1> transitions;
			} stopped;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 2> transitions;
			} broken;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 3> transitions;
			} repairing;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 2> transitions;
			} evacuating;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 0> transitions;
			} interrupted;
			QString status;
			bool isShutdown;

			Members(ServiceStateInterface * p_parent):
				stateMachine(new ServiceStateMachine(p_parent)),
				starting{new QState(stateMachine), nullptr, {}},
			started{new QState(stateMachine), nullptr, {}, nullptr},
			stopping{new QState(stateMachine), nullptr, {}},
			stopped{new QState(stateMachine), nullptr, {}},
			broken{new QState(stateMachine), nullptr, {}},
			repairing{new QState(stateMachine), nullptr, {}},
			evacuating{new QState(stateMachine), nullptr, {}},
			interrupted{new QState(stateMachine), nullptr, {}},
			isShutdown(false)
			{
				started.interface = new ServiceStartedStateInterface(p_parent, started.persistent);
			}
		};

		MPtr<Members> m;
};

}
}
}

#endif

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
