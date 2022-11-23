#include <cutehmi/services/StateInterface.hpp>

namespace cutehmi {
namespace services {

QAbstractState * StateInterface::stopped() const
{
	return m->stopped;
}

QAbstractState * StateInterface::starting() const
{
	return m->starting;
}

QAbstractState * StateInterface::started() const
{
	return m->started;
}

QAbstractState * StateInterface::stopping() const
{
	return m->stopping;
}

QAbstractState * StateInterface::broken() const
{
	return m->broken;
}

QAbstractState * StateInterface::repairing() const
{
	return m->repairing;
}

QAbstractState * StateInterface::evacuating() const
{
	return m->evacuating;
}

QAbstractState * StateInterface::interrupted() const
{
	return m->interrupted;
}

StartedStateInterface * StateInterface::startedStates() const
{
	return m->startedStateInterface;
}

QAbstractState * StateInterface::findState(const QString & name) const
{
	for (auto && state : {
					m->stopped,
					m->starting,
					m->started,
					m->stopping,
					m->broken,
					m->repairing,
					m->evacuating,
					m->interrupted
			}) {
		QAbstractState * child = state->findChild<QAbstractState *>(name);
		if (child)
			return child;
	}

	return nullptr;
}

StateInterface::StateInterface():
	m(new Members{
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	new StartedStateInterface(this)})
{
}


void StateInterface::setStopped(QAbstractState * stopped)
{
	if (m->stopped != stopped) {
		m->stopped = stopped;
		emit stoppedChanged();
	}
}

void StateInterface::setStarting(QAbstractState * starting)
{
	if (m->starting != starting) {
		m->starting = starting;
		emit startingChanged();
	}
}

void StateInterface::setStarted(QAbstractState * started, QAbstractState * yielding, QAbstractState * active, QAbstractState * idling)
{
	m->startedStateInterface->setYielding(yielding);
	m->startedStateInterface->setActive(active);
	m->startedStateInterface->setIdling(idling);
	if (m->started != started) {
		m->started = started;
		emit startedChanged();
	}
}

void StateInterface::setStopping(QAbstractState * stopping)
{
	if (m->stopping != stopping) {
		m->stopping = stopping;
		emit stoppingChanged();
	}
}

void StateInterface::setBroken(QAbstractState * broken)
{
	if (m->broken != broken) {
		m->broken = broken;
		emit brokenChanged();
	}
}

void StateInterface::setRepairing(QAbstractState * repairing)
{
	if (m->repairing != repairing) {
		m->repairing = repairing;
		emit repairingChanged();
	}
}

void StateInterface::setEvacuating(QAbstractState * evacuating)
{
	if (m->evacuating != evacuating) {
		m->evacuating = evacuating;
		emit evacuatingChanged();
	}
}

void StateInterface::setInterrupted(QAbstractState * interrupted)
{
	if (m->interrupted != interrupted) {
		m->interrupted = interrupted;
		emit interruptedChanged();
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
