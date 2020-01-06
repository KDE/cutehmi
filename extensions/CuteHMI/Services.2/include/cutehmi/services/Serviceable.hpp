#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICEABLE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICEABLE_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QState>
#include <QSignalTransition>

namespace cutehmi {
namespace services {

/**
 * %Serviceable interface. By implementing this interface object is allowed to be embedded inside Service instance.
 *
 * Implementing Serviceable interface involves configuring states and defining transitions. During configuration state interface
 * can be extended by adding additional child states to the states passed by configuration functions.
 *
 * Standard states and transitions are shown on the following state chart diagram.
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
		typedef QHash<QState *, QString> ServiceStatuses;

		Serviceable() = default;

		/**
		 * Configure started state. Started state is not directly accessible. Intead its child states shall be configured.
		 * @param active active state.
		 * @param idling idling state.
		 * @param yielding yielding state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureStarted(QState * active, const QState * idling, const QState * yielding) = 0;

		/**
		 * Configure starting state.
		 * @param starting state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureStarting(QState * starting) = 0;

		/**
		 * Configure stopping state.
		 * @param stopping state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureStopping(QState * stopping) = 0;

		/**
		 * Configure broken state.
		 * @param broken state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureBroken(QState * broken) = 0;

		/**
		 * Configure repairing state.
		 * @param repairing state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureRepairing(QState * repairing) = 0;

		/**
		 * Configure evacuating state.
		 * @param evacuating state.
		 * @return optional hash map containing status name for each state or @p nullptr if default statuses should be used.
		 */
		virtual std::unique_ptr<ServiceStatuses> configureEvacuating(QState * evacuating) = 0;

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
		virtual ~Serviceable() = default;

		Serviceable(const Serviceable & other) = default;

		Serviceable & operator =(const Serviceable & other) = default;
};

}
}

Q_DECLARE_METATYPE(cutehmi::services::Serviceable *)

#endif

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
