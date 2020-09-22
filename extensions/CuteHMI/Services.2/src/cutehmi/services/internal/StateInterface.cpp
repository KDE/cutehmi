#include <cutehmi/services/internal/StateInterface.hpp>

namespace cutehmi {
namespace services {
namespace internal {

StateInterface::StateInterface(QObject * parent):
	QObject(parent),
	m(new Members)
{
	m->mainStates[Members::STARTED].setInitialState(m->yielding);

	m->mainStates[Members::STOPPED].setObjectName("stopped");
	m->mainStates[Members::INTERRUPTED].setObjectName("interrupted");
	m->mainStates[Members::STARTING].setObjectName("starting");
	m->mainStates[Members::STARTED].setObjectName("started");
	m->mainStates[Members::STOPPING].setObjectName("stopping");
	m->mainStates[Members::BROKEN].setObjectName("broken");
	m->mainStates[Members::REPAIRING].setObjectName("repairing");
	m->mainStates[Members::EVACUATING].setObjectName("evacuating");
	m->active->setObjectName("active");
	m->idling->setObjectName("idling");
	m->yielding->setObjectName("yielding");
}

QString StateInterface::status() const
{
	return m->status;
}

void StateInterface::setStatus(const QString & status)
{
	if (m->status != status) {
		m->status = status;
		emit statusChanged();
	}
}

QAbstractState * StateInterface::find(const QString & name)
{
	for (auto state = m->mainStates.begin(); state != m->mainStates.end(); ++state) {
		if (name == state->objectName())
			return & (*state);
		QAbstractState * child = state->findChild<QAbstractState *>(name);
		if (child)
			return child;
	}
	return nullptr;
}

QState & StateInterface::stopped()
{
	return m->mainStates[Members::STOPPED];
}

const QState & StateInterface::stopped() const
{
	return m->mainStates[Members::STOPPED];
}

QState & StateInterface::interrupted()
{
	return m->mainStates[Members::INTERRUPTED];
}

const QState & StateInterface::interrupted() const
{
	return m->mainStates[Members::INTERRUPTED];
}

QState & StateInterface::starting()
{
	return m->mainStates[Members::STARTING];
}

const QState & StateInterface::starting() const
{
	return m->mainStates[Members::STARTING];
}

QState & StateInterface::started()
{
	return m->mainStates[Members::STARTED];
}

const QState & StateInterface::started() const
{
	return m->mainStates[Members::STARTED];
}

QState & StateInterface::idling()
{
	return *m->idling;
}

const QState & StateInterface::idling() const
{
	return *m->idling;
}

QState & StateInterface::yielding()
{
	return *m->yielding;
}

const QState & StateInterface::yielding() const
{
	return *m->yielding;
}

QState & StateInterface::active()
{
	return *m->active;
}

const QState & StateInterface::active() const
{
	return *m->active;
}

QState & StateInterface::stopping()
{
	return m->mainStates[Members::STOPPING];
}

const QState & StateInterface::stopping() const
{
	return m->mainStates[Members::STOPPING];
}

QState & StateInterface::broken()
{
	return m->mainStates[Members::BROKEN];
}

const QState & StateInterface::borken() const
{
	return m->mainStates[Members::BROKEN];
}

QState & StateInterface::repairing()
{
	return m->mainStates[Members::REPAIRING];
}

const QState & StateInterface::repairing() const
{
	return m->mainStates[Members::REPAIRING];
}

QState & StateInterface::evacuating()
{
	return m->mainStates[Members::EVACUATING];
}

const QState & StateInterface::evacuating() const
{
	return m->mainStates[Members::EVACUATING];
}

}
}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
