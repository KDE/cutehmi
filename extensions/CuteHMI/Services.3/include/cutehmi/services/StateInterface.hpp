#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_STATEINTERFACE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_STATEINTERFACE_HPP

#include "internal/common.hpp"
#include "StartedStateInterface.hpp"

#include <QObject>
#include <QQmlEngine>

namespace cutehmi {
namespace services {

class AbstractService;

/**
 * %State interface.
 *
 * %State interface is basically a predefined state machine configuration, which can be utilized and extended by the service.
 *
 * States and transitions can be customized through Serviceable interface. %State passed to the Serviceable are not exactly the same
 * ones as the ones available as StateInterface properties however. Each state comes up with two flavors - persistent and ephemeric.
 * Each ephemeric state has a persistent parent. Ephemeric children can be deleted and recreated. They are the ones which are passed
 * to Servicable functions. This allows the service to be reconfigured from the inside when necessary, while keeping external
 * states and any existing signal-slot connections they may have intact. Typically you should rely on persistent states and don't
 * bother about ephemeric variants, but this information is given to avoid confusion when dealing with Serviceable and noticing that
 * it's using different state objects.
 */
class CUTEHMI_SERVICES_API StateInterface:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(StateInterface)
		QML_UNCREATABLE("StateInterface is an abstract class")

	public:
		Q_PROPERTY(QAbstractState * stopped READ stopped CONSTANT)

		Q_PROPERTY(QAbstractState * starting READ starting CONSTANT)

		Q_PROPERTY(QAbstractState * started READ started CONSTANT)

		Q_PROPERTY(QAbstractState * stopping READ stopping CONSTANT)

		Q_PROPERTY(QAbstractState * broken READ broken CONSTANT)

		Q_PROPERTY(QAbstractState * repairing READ repairing CONSTANT)

		Q_PROPERTY(QAbstractState * evacuating READ evacuating CONSTANT)

		Q_PROPERTY(QAbstractState * interrupted READ interrupted CONSTANT)

		Q_PROPERTY(cutehmi::services::StartedStateInterface * startedStates READ startedStates CONSTANT)

		virtual QAbstractState * stopped() const = 0;

		virtual QAbstractState * starting() const = 0;

		virtual QAbstractState * started() const = 0;

		virtual QAbstractState * stopping() const = 0;

		virtual QAbstractState * broken() const = 0;

		virtual QAbstractState * repairing() const = 0;

		virtual QAbstractState * evacuating() const = 0;

		virtual QAbstractState * interrupted() const = 0;

		virtual cutehmi::services::StartedStateInterface * startedStates() const = 0;

		/**
		 * Find state by its name. States can be given name using QObject::setObjectName() function. Standard states have following
		 * names:
		 * - @p "stopped" and @p "stopped.ephemeric"
		 * - @p "interrupted" and @p "interrupted.ephemeric"
		 * - @p "starting" and @p "starting.ephemeric"
		 * - @p "started" and @p "started.ephemeric"
		 * - @p "stopping" and @p "stopping.ephemeric"
		 * - @p "broken" and @p "broken.ephemeric"
		 * - @p "repairing" and @p "repairing.ephemeric"
		 * - @p "evacuating" and @p "evacuating.ephemeric"
		 * - @p "started.active" and @p "started.active.ephemeric"
		 * - @p "started.idling" and @p "started.idling.ephemeric"
		 * - @p "started.yielding" and @p "started.yielding.ephemeric".
		 * .
		 * @param name state name.
		 * @return state.
		 */
		Q_INVOKABLE QAbstractState * findState(const QString & name) const;

	protected:
		AbstractService * service() const;
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
