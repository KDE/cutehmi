#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_STATEINTERFACE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_STATEINTERFACE_HPP

#include "internal/common.hpp"
#include "StartedStateInterface.hpp"

#include <QObject>
#include <QAbstractState>

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API StateInterface:
	public QObject
{
		Q_OBJECT

	public:
		Q_PROPERTY(QAbstractState * stopped READ stopped NOTIFY stoppedChanged)

		Q_PROPERTY(QAbstractState * starting READ starting NOTIFY startingChanged)

		Q_PROPERTY(QAbstractState * started READ started NOTIFY startedChanged)

		Q_PROPERTY(QAbstractState * stopping READ stopping NOTIFY stoppingChanged)

		Q_PROPERTY(QAbstractState * broken READ broken NOTIFY brokenChanged)

		Q_PROPERTY(QAbstractState * repairing READ repairing NOTIFY repairingChanged)

		Q_PROPERTY(QAbstractState * evacuating READ evacuating NOTIFY evacuatingChanged)

		Q_PROPERTY(QAbstractState * interrupted READ interrupted NOTIFY interruptedChanged)

		Q_PROPERTY(cutehmi::services::StartedStateInterface * startedStates READ startedStates CONSTANT)

		QAbstractState * stopped() const;

		QAbstractState * starting() const;

		QAbstractState * started() const;

		QAbstractState * stopping() const;

		QAbstractState * broken() const;

		QAbstractState * repairing() const;

		QAbstractState * evacuating() const;

		QAbstractState * interrupted() const;

		cutehmi::services::StartedStateInterface * startedStates() const;

		/**
		 * Find state by its name. States can be given name using QObject::setObjectName() function. Standard states have following
		 * names:
		 * - @p "stopped"
		 * - @p "interrupted"
		 * - @p "starting"
		 * - @p "started"
		 * - @p "stopping"
		 * - @p "broken"
		 * - @p "repairing"
		 * - @p "evacuating"
		 * - @p "started.active"
		 * - @p "started.idling"
		 * - @p "started.yielding"
		 * .
		 * @param name state name.
		 * @return state.
		 */
		Q_INVOKABLE QAbstractState * findState(const QString & name) const;

	signals:
		void stoppedChanged();

		void startingChanged();

		void startedChanged();

		void stoppingChanged();

		void brokenChanged();

		void repairingChanged();

		void evacuatingChanged();

		void interruptedChanged();

	protected:
		StateInterface();

		void setStopped(QAbstractState * stopped);

		void setStarting(QAbstractState * starting);

		void setStarted(QAbstractState * started, QAbstractState * yielding, QAbstractState * active, QAbstractState * idling);

		void setStopping(QAbstractState * stopping);

		void setBroken(QAbstractState * broken);

		void setRepairing(QAbstractState * repairing);

		void setEvacuating(QAbstractState * evacuating);

		void setInterrupted(QAbstractState * interrupted);

	private:
		struct Members {
			QAbstractState * stopped;
			QAbstractState * starting;
			QAbstractState * started;
			QAbstractState * stopping;
			QAbstractState * broken;
			QAbstractState * repairing;
			QAbstractState * evacuating;
			QAbstractState * interrupted;
			StartedStateInterface * startedStateInterface;
		};

		MPtr<Members> m;
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
