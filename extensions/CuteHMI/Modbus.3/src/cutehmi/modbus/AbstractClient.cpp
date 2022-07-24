#include <cutehmi/modbus/AbstractClient.hpp>

#include <QTimer>

namespace cutehmi {
namespace modbus {

constexpr int AbstractClient::INITIAL_POLLING_INTERVAL;
constexpr int AbstractClient::INITIAL_POLLING_TASK_INTERVAL;

int AbstractClient::pollingInterval() const
{
	return m->pollingInterval;
}

void AbstractClient::setPollingInterval(int interval)
{
	if (m->pollingInterval != interval) {
		m->pollingInterval = interval;
		emit pollingIntervalChanged();
	}
}

int AbstractClient::pollingTaskInterval() const
{
	return m->pollingTaskInterval;
}

void AbstractClient::setPollingTaskInterval(int interval)
{
	if (m->pollingTaskInterval != interval) {
		m->pollingTaskInterval = interval;
		emit pollingTaskIntervalChanged();
	}
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractClient::configureStarting(QState * starting)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * connecting = new QState(starting);
	starting->setInitialState(connecting);
	statuses->insert(connecting, tr("Connecting"));
	connect(connecting, & QState::entered, this, & AbstractClient::open);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractClient::configureStarted(QState * active, const QState * idling, const QState * yielding)
{
	Q_UNUSED(yielding)

	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	connect(idling, & QState::entered, this, [this] {
		QTimer::singleShot(pollingInterval(), this, [this]{
			emit pollingRequested();
		});
	});

	QState * polling = new QState(active);
	active->setInitialState(polling);
	statuses->insert(polling, tr("Polling"));
	connect(polling, & QState::entered, this, & AbstractClient::poll);

	QState * pollingTask = new QState(polling);
	polling->setInitialState(pollingTask);
	connect(pollingTask, & QState::entered, this, & AbstractClient::pollingTask);

	QState * pollingWait = new QState(polling);
	connect(pollingWait, & QState::entered, this, [this] {
		QTimer::singleShot(pollingTaskInterval(), this, [this]{
			emit pollingTaskRequested();
		});
	});

	pollingTask->addTransition(this, & AbstractClient::pollingTaskFinished, pollingWait);

	pollingWait->addTransition(this, & AbstractClient::pollingTaskRequested, pollingTask);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractClient::configureStopping(QState * stopping)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * disconnecting = new QState(stopping);
	stopping->setInitialState(disconnecting);
	statuses->insert(disconnecting, tr("Disconnecting"));
	connect(disconnecting, & QState::entered, this, & AbstractClient::close);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractClient::configureBroken(QState * broken)
{
	connect(broken, & QState::entered, this, & AbstractClient::close);

	return nullptr;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractClient::configureRepairing(QState * repairing)
{
	connect(repairing, & QState::entered, this, & AbstractClient::open);

	return nullptr;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractClient::configureEvacuating(QState * evacuating)
{
	connect(evacuating, & QState::entered, this, & AbstractClient::stopped);

	return nullptr;
}

std::unique_ptr<QAbstractTransition> AbstractClient::transitionToStarted() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractClient::started);
}

std::unique_ptr<QAbstractTransition> AbstractClient::transitionToStopped() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractClient::stopped);
}

std::unique_ptr<QAbstractTransition> AbstractClient::transitionToBroken() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractClient::broke);
}

std::unique_ptr<QAbstractTransition> AbstractClient::transitionToYielding() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractClient::pollingRequested);
}

std::unique_ptr<QAbstractTransition> AbstractClient::transitionToIdling() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractClient::pollingFinished);
}

AbstractClient::AbstractClient(QObject * parent):
	AbstractDevice(parent),
	m(new Members(this))
{
	connect(this, & AbstractDevice::stateChanged, this, & AbstractClient::onStateChanged);
}

void AbstractClient::handleRequest(const QJsonObject & request)
{
	emit requestReceived(request);
}

void AbstractClient::handleReply(QUuid requestId, QJsonObject reply)
{
	AbstractDevice::handleReply(requestId, reply);

	if (requestId == m->pollingIterator.requestId())
		emit pollingTaskFinished();
}

void AbstractClient::onStateChanged()
{
	if (state() == AbstractDevice::OPENED)
		setReady(true);
	else
		setReady(false);
}

void AbstractClient::poll()
{
	m->pollingIterator.reset();
}

void AbstractClient::pollingTask()
{
	if (!m->pollingIterator.runNext())
		emit pollingFinished();
}

}
}

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
