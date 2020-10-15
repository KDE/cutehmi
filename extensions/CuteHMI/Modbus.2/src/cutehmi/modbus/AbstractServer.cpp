#include <cutehmi/modbus/AbstractServer.hpp>

namespace cutehmi {
namespace modbus {

constexpr bool AbstractServer::INITIAL_BUSY;

AbstractServer::AbstractServer(QObject * parent):
	AbstractDevice(parent),
	m(new Members)
{
	setReady(true);
}

bool AbstractServer::busy() const
{
	return m->busy;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractServer::configureStarting(QState * starting)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * opening = new QState(starting);
	starting->setInitialState(opening);
	statuses->insert(opening, tr("Initiating listening"));
	connect(opening, & QState::entered, this, & AbstractServer::open);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractServer::configureStarted(QState * active, const QState * idling, const QState * yielding)
{
	Q_UNUSED(active)
	Q_UNUSED(idling)
	Q_UNUSED(yielding)

	return nullptr;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractServer::configureStopping(QState * stopping)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * closing = new QState(stopping);
	stopping->setInitialState(closing);
	statuses->insert(closing, tr("Closing"));
	connect(closing, & QState::entered, this, & AbstractServer::close);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractServer::configureBroken(QState * broken)
{
	connect(broken, & QState::entered, this, & AbstractServer::close);

	return nullptr;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractServer::configureRepairing(QState * repairing)
{
	connect(repairing, & QState::entered, this, & AbstractServer::open);

	return nullptr;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractServer::configureEvacuating(QState * evacuating)
{
	connect(evacuating, & QState::entered, this, & AbstractServer::stopped);

	return nullptr;
}

std::unique_ptr<QAbstractTransition> AbstractServer::transitionToStarted() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractServer::started);
}

std::unique_ptr<QAbstractTransition> AbstractServer::transitionToStopped() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractServer::stopped);
}

std::unique_ptr<QAbstractTransition> AbstractServer::transitionToBroken() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractServer::broke);
}

std::unique_ptr<QAbstractTransition> AbstractServer::transitionToYielding() const
{
	return nullptr;
}

std::unique_ptr<QAbstractTransition> AbstractServer::transitionToIdling() const
{
	return nullptr;
}

void AbstractServer::handleRequest(const QJsonObject & request)
{
	emit requestReceived(request);
}

void AbstractServer::handleCoilsWritten(quint16 address, quint16 amount)
{
	requestReadCoils(address, amount);
}

void AbstractServer::handleDiscreteInputsWritten(quint16 address, quint16 amount)
{
	requestReadDiscreteInputs(address, amount);
}

void AbstractServer::handleHoldingRegistersWritten(quint16 address, quint16 amount)
{
	requestReadHoldingRegisters(address, amount);
}

void AbstractServer::handleInputRegistersWritten(quint16 address, quint16 amount)
{
	requestReadInputRegisters(address, amount);
}

void AbstractServer::updateBusy(bool busy)
{
	if (m->busy != busy) {
		m->busy = busy;
		emit busyChanged();
	}
}

}
}

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
