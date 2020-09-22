#include <cutehmi/dataacquisition/AbstractListModel.hpp>

namespace cutehmi {
namespace dataacquisition {

constexpr int AbstractListModel::INITIAL_INTERVAL;

AbstractListModel::AbstractListModel(QObject * parent):
	QAbstractListModel(parent),
	m(new Members)
{
	m->updateTimer.setSingleShot(true);
}

int AbstractListModel::interval() const
{
	return m->interval;
}

void AbstractListModel::setInterval(int interval)
{
	CUTEHMI_ASSERT(interval >= 0, "Value of 'interval' property should be non-negative.");

	if (m->interval != interval) {
		m->interval = interval;
		emit intervalChanged();
	}
}

Schema * AbstractListModel::schema() const
{
	return m->schema;
}

void AbstractListModel::setSchema(Schema * schema)
{
	if (m->schema != schema) {
		if (m->schema)
			m->schema->disconnect(this);

		m->schema = schema;
		emit schemaChanged();

		if (m->schema) {
			connect(m->schema, & Schema::validated, this, & AbstractListModel::onSchemaValidated);
			connect(m->schema, & Schema::errored, this, & AbstractListModel::broke);
		}
	}
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractListModel::configureStarting(QState * starting)
{
	return configureStartingOrRepairing(starting);
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractListModel::configureStarted(QState * active, const QState * idling, const QState * yielding)
{
	Q_UNUSED(yielding)

	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	connect(idling, & QState::entered, this, & AbstractListModel::startUpdateTimer);

	QState * updating = new QState(active);
	statuses->insert(updating, tr("Updating model"));
	active->setInitialState(updating);
	connect(updating, & QState::entered, this, & AbstractListModel::requestUpdate);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractListModel::configureStopping(QState * stopping)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * waitingForWorkers = new QState(stopping);
	statuses->insert(waitingForWorkers, tr("Waiting for finishing an update"));
	connect(waitingForWorkers, & QState::entered, this, & AbstractListModel::confirmUpdateFinished);

	QState * stoppingTimer = new QState(stopping);
	stopping->setInitialState(stoppingTimer);
	statuses->insert(stoppingTimer, tr("Stopping update timer"));
	connect(stoppingTimer, & QState::entered, this, & AbstractListModel::stopUpdateTimer);
	stoppingTimer->addTransition(this, & AbstractListModel::updateTimerStopped, waitingForWorkers);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractListModel::configureBroken(QState * broken)
{
	connect(broken, & QState::entered, this, & AbstractListModel::stopUpdateTimer);

	return nullptr;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractListModel::configureRepairing(QState * repairing)
{
	return configureStartingOrRepairing(repairing);
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractListModel::configureEvacuating(QState * evacuating)
{
	connect(evacuating, & QState::entered, this, & AbstractListModel::stopped);

	return nullptr;
}

std::unique_ptr<QAbstractTransition> AbstractListModel::transitionToStarted() const
{
	connect(this, & AbstractListModel::updateTimerStarted, this, & AbstractListModel::started);

	return std::make_unique<QSignalTransition>(this, & AbstractListModel::started);
}

std::unique_ptr<QAbstractTransition> AbstractListModel::transitionToStopped() const
{
	connect(this, & AbstractListModel::updateFinished, this, & AbstractListModel::stopped);

	return std::make_unique<QSignalTransition>(this, & AbstractListModel::stopped);
}

std::unique_ptr<QAbstractTransition> AbstractListModel::transitionToBroken() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractListModel::broke);
}

std::unique_ptr<QAbstractTransition> AbstractListModel::transitionToYielding() const
{
	return std::make_unique<QSignalTransition>(& m->updateTimer, & QTimer::timeout);
}

std::unique_ptr<QAbstractTransition> AbstractListModel::transitionToIdling() const
{
	return std::make_unique<QSignalTransition>(this, & AbstractListModel::updateFinished);
}

void AbstractListModel::onSchemaValidated(bool result)
{
	if (result)
		emit schemaValidated();
	else
		emit broke();
}

void AbstractListModel::startUpdateTimer()
{
	m->updateTimer.start(interval());
	emit updateTimerStarted();
}

void AbstractListModel::stopUpdateTimer()
{
	m->updateTimer.stop();
	emit updateTimerStopped();
}

std::unique_ptr<services::Serviceable::ServiceStatuses> AbstractListModel::configureStartingOrRepairing(QState * parent)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * startingTimer = new QState(parent);
	statuses->insert(startingTimer, tr("Starting store timer"));
	connect(startingTimer, & QState::entered, this, & AbstractListModel::startUpdateTimer);

	QState * validatingSchema = createValidatingSchemaSate(parent, statuses.get(), startingTimer);

	QState * waitingForDatabase = createWaitingForDatabaseConnectedSate(parent, statuses.get(), validatingSchema);
	parent->setInitialState(waitingForDatabase);

	return statuses;
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
