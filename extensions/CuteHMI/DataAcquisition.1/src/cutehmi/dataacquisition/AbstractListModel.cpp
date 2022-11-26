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

void AbstractListModel::configureStarting(QState * starting, AssignStatusFunction assignStatus)
{
	configureStartingOrRepairing(starting, assignStatus);
}

void AbstractListModel::configureStarted(QState * active, const QState * idling, const QState * yielding, AssignStatusFunction assignStatus)
{
	Q_UNUSED(yielding)

	connect(idling, & QState::entered, this, & AbstractListModel::startUpdateTimer);

	QState * updating = new QState(active);
	assignStatus(*updating, tr("Updating model"));
	active->setInitialState(updating);
	connect(updating, & QState::entered, this, & AbstractListModel::requestUpdate);
}

void AbstractListModel::configureStopping(QState * stopping, AssignStatusFunction assignStatus)
{
	QState * waitingForWorkers = new QState(stopping);
	assignStatus(*waitingForWorkers, tr("Waiting for finishing an update"));
	connect(waitingForWorkers, & QState::entered, this, & AbstractListModel::confirmUpdateFinished);

	QState * stoppingTimer = new QState(stopping);
	stopping->setInitialState(stoppingTimer);
	assignStatus(*stoppingTimer, tr("Stopping update timer"));
	connect(stoppingTimer, & QState::entered, this, & AbstractListModel::stopUpdateTimer);
	stoppingTimer->addTransition(this, & AbstractListModel::updateTimerStopped, waitingForWorkers);
}

void AbstractListModel::configureBroken(QState * broken, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	connect(broken, & QState::entered, this, & AbstractListModel::stopUpdateTimer);
}

void AbstractListModel::configureRepairing(QState * repairing, AssignStatusFunction assignStatus)
{
	configureStartingOrRepairing(repairing, assignStatus);
}

void AbstractListModel::configureEvacuating(QState * evacuating, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	connect(evacuating, & QState::entered, this, & AbstractListModel::stopped);
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

void AbstractListModel::configureStartingOrRepairing(QState * parent, AssignStatusFunction assignStatus)
{
	QState * startingTimer = new QState(parent);
	assignStatus(*startingTimer, tr("Starting store timer"));
	connect(startingTimer, & QState::entered, this, & AbstractListModel::startUpdateTimer);

	QState * validatingSchema = createValidatingSchemaSate(parent, assignStatus, startingTimer);

	QState * waitingForDatabase = createWaitingForDatabaseConnectedSate(parent, assignStatus, validatingSchema);
	parent->setInitialState(waitingForDatabase);
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
