#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEABLE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEABLE_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QState>
#include <QSignalTransition>

#include <utility>

namespace cutehmi {
namespace services {

/**
 * %Serviceable interface. By implementing this interface object is allowed to be embedded inside Service instance.
 *
 * Implementing Serviceable interface involves configuring states and defining transitions. During configuration state interface
 * can be extended by adding additional child states to the states passed by configuration functions.
 *
 * Standard states and transitions are shown on the following state chart diagram.
 * @anchor cutehmi-services-state-interface-diagram
 * @image html doc/standard_states.png "State interface"
 * @image latex doc/standard_states.png "State interface"
 *
 * Implementing object can utilize the state machine according to its needs by:
 *		- defining when standard transitions take place (and likely trigger them)
 *		- adding custom states to the standard ones
 *		- connecting slots to QState signals (custom or standard ones)
 *		.
 */
class CUTEHMI_SERVICES_API Serviceable
{
	public:
		typedef std::function<void (QState & state, const QString & status)> AssignStatusFunction;

		/**
		 * Configure starting state.
		 * @param starting state.
		 * @param assignStatus a function callback that allows one to associate the state with custom service status.
		 */
		virtual void configureStarting(QState * starting, AssignStatusFunction assignStatus) = 0;

		/**
		 * Configure started state. Started state is not directly accessible. Intead its child states shall be configured.
		 * @param active active state. In this state any resource-hungry and intense operations shall be performed. Serviceable
		 * object may add child states to @a active state for its own use.
		 * @param idling idling state. In this state a serviceable should not perform any intense operations or consume resources.
		 * Serviceable decides by itself when to enter idling state. Some objects may never activate the transition to idling state.
		 * When serviceable object is ready to become active again it should signal it by activating transitionToIdling(). No child
		 * states can be added to idling state.
		 * @param yielding yielding state. In this state a service should not perform any intense operations or consume resources.
		 * It should just wait until it is activated, therefore no child states can be added to @a yielding state.
		 * @param assignStatus a function callback that allows one to associate the state with custom service status.
		 */
		virtual void configureStarted(QState * active, const QState * idling, const QState * yielding, AssignStatusFunction assignStatus) = 0;

		/**
		 * Configure stopping state.
		 * @param stopping state.
		 * @param assignStatus a function callback that allows one to associate the state with custom service status.
		 */
		virtual void configureStopping(QState * stopping, AssignStatusFunction assignStatus) = 0;

		/**
		 * Configure broken state.
		 * @param broken state.
		 * @param assignStatus a function callback that allows one to associate the state with custom service status.
		 */
		virtual void configureBroken(QState * broken, AssignStatusFunction assignStatus) = 0;

		/**
		 * Configure repairing state.
		 * @param repairing state.
		 * @param assignStatus a function callback that allows one to associate the state with custom service status.
		 */
		virtual void configureRepairing(QState * repairing, AssignStatusFunction assignStatus) = 0;

		/**
		 * Configure evacuating state.
		 * @param evacuating state.
		 * @param assignStatus a function callback that allows one to associate the state with custom service status.
		 */
		virtual void configureEvacuating(QState * evacuating, AssignStatusFunction assignStatus) = 0;

		/**
		 * Transition to started state.
		 * @return transition to started state. It is allowed to return @p nullptr. In such case transition from starting to
		 * started state will be immediate.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToStarted() const = 0;

		/**
		 * Transition to stopped state.
		 * @return transition to stopped state. It is allowed to return @p nullptr. In such case transition from stopping to
		 * stopped state will be immediate.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToStopped() const = 0;

		/**
		 * Transition to broken state.
		 * @return transition to broken state. It is allowed to return @p nullptr. In such case service will never enter broken
		 * or repairing states.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToBroken() const = 0;

		/**
		 * Transition to yielding state.
		 * @return transition to yielding state. It is allowed to return @p nullptr. In such case service will skip yielding
		 * state and immediately become active. This will make service impolite.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToYielding() const = 0;

		/**
		 * Transition to idling state.
		 * @return transition to idling state. It is allowed to return @p nullptr. In such case service will not enter idling
		 * state and will remain persistently active. This will make service impolite.
		 */
		virtual std::unique_ptr<QAbstractTransition> transitionToIdling() const = 0;

	protected:
		Serviceable() = default;

		virtual ~Serviceable() = default;

		Serviceable(const Serviceable & other) = default;

		Serviceable & operator =(const Serviceable & other) = default;
};

}
}

Q_DECLARE_METATYPE(cutehmi::services::Serviceable *)

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
