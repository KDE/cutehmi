#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEGROUPRULE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEGROUPRULE_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QQmlEngine>
#include <QAbstractTransition>

namespace cutehmi {
namespace services {

class AbstractService;

/**
 * Service group rule.
 *
 * Service group rules are applied by ServiceGroup to customize the process of starting, stopping or activating the services.
 * Internally for each service a substate is created in the ServiceGroup state configured via Serviceable interface (such as
 * starting, stopping, repairing, active). Service group will then query its ServiceGroupRule objects by calling
 * conditionalTransition() function. If confitionalTransition() returns non-null value, then additional, subsequent substate is
 * prepended and the returned transition object is used to define the transition between them.
 */
class CUTEHMI_SERVICES_API ServiceGroupRule:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(ServiceGroupRule)
		QML_UNCREATABLE("ServiceGroupRule is an abstract class")

	public:
		enum SlotType {
			SERVICE_START,
			SERVICE_STOP,
			SERVICE_ACTIVATE
		};

		/**
		 * Get conditional transition that should be applied to a particular service and slot type.
		 * @param type slot type. States to which the transtion should be applied are defined by slot type. Enum values correspond to
		 * AbstractService::start(), AbstractService::stop() and AbstractService::activate() slots. See the
		 * @ref cutehmi-services-state-interface-diagram "state interface diagram" to determine, which states are activated by
		 * signals related to these slots (signals are named using past perfect verbs: start - started, stop - stopped, activate -
		 * activated). The transition will be applied to a newly created substate for the the relevant, existing substate belonging
		 * to the related group state and dedicated for a particular @a service.
		 * @param service service belonging to the group for which the transition might be potentially applied.
		 * @return transition object or @p nullptr if no transition shall be applied to a particular @a service and state related to
		 * a particular @a slot.
		 */
		virtual std::unique_ptr<QAbstractTransition> conditionalTransition(SlotType type, const AbstractService * service) = 0;

	protected:
		explicit ServiceGroupRule(QObject * parent = nullptr);
};

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
