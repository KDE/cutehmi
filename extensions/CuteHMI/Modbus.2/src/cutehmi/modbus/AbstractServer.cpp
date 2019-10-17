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

std::unique_ptr<services::Serviceable::ServiceStatuses> cutehmi::modbus::AbstractServer::configureStopping(QState * stopping)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * closing = new QState(stopping);
	stopping->setInitialState(closing);
	statuses->insert(closing, tr("Closing"));
	connect(closing, & QState::entered, this, & AbstractServer::close);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> cutehmi::modbus::AbstractServer::configureBroken(QState * broken)
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

std::unique_ptr<QAbstractTransition> cutehmi::modbus::AbstractServer::transitionToIdling() const
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

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
