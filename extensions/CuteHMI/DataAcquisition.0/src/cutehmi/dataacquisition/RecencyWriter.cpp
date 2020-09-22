#include <cutehmi/dataacquisition/RecencyWriter.hpp>

namespace cutehmi {
namespace dataacquisition {

constexpr int RecencyWriter::INITIAL_INTERVAL;

RecencyWriter::RecencyWriter(QObject * parent):
	AbstractWriter(parent),
	m(new Members)
{
	m->updateTimer.setSingleShot(true);
	connect(this, & AbstractWriter::schemaChanged, this, & RecencyWriter::onSchemaChanged);
	connect(& m->dbCollective, & internal::RecencyCollective::busyChanged, this, & RecencyWriter::confirmCollectiveFinished);
}

int RecencyWriter::interval() const
{
	return m->interval;
}

void RecencyWriter::setInterval(int interval)
{
	CUTEHMI_ASSERT(interval >= 0, "Value of 'interval' property should be non-negative.");

	if (m->interval != interval) {
		m->interval = interval;
		emit intervalChanged();
	}
}

std::unique_ptr<services::Serviceable::ServiceStatuses> RecencyWriter::configureStarting(QState * starting)
{
	return configureStartingOrRepairing(starting);
}

std::unique_ptr<services::Serviceable::ServiceStatuses> RecencyWriter::configureStarted(QState * active, const QState * idling, const QState * yielding)
{
	Q_UNUSED(yielding)

	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	connect(idling, & QState::entered, this, & RecencyWriter::startUpdateTimer);

	QState * updating = new QState(active);
	statuses->insert(updating, tr("Updating values"));
	active->setInitialState(updating);
	connect(updating, & QState::entered, this, & RecencyWriter::updateValues);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> RecencyWriter::configureStopping(QState * stopping)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * waitingForWorkers = new QState(stopping);
	statuses->insert(waitingForWorkers, tr("Waiting for database workers to finish"));
	connect(waitingForWorkers, & QState::entered, this, & RecencyWriter::confirmCollectiveFinished);

	QState * stoppingTimer = new QState(stopping);
	stopping->setInitialState(stoppingTimer);
	statuses->insert(stoppingTimer, tr("Stopping store timer"));
	connect(stoppingTimer, & QState::entered, this, & RecencyWriter::stopUpdateTimer);
	stoppingTimer->addTransition(this, & RecencyWriter::updateTimerStopped, waitingForWorkers);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> RecencyWriter::configureBroken(QState * broken)
{
	connect(broken, & QState::entered, this, & RecencyWriter::stopUpdateTimer);

	return nullptr;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> RecencyWriter::configureRepairing(QState * repairing)
{
	return configureStartingOrRepairing(repairing);
}

std::unique_ptr<services::Serviceable::ServiceStatuses> RecencyWriter::configureEvacuating(QState * evacuating)
{
	connect(evacuating, & QState::entered, this, & RecencyWriter::stopped);

	return nullptr;
}

std::unique_ptr<QAbstractTransition> RecencyWriter::transitionToStarted() const
{
	connect(this, & RecencyWriter::updateTimerStarted, this, & RecencyWriter::started);

	return std::make_unique<QSignalTransition>(this, & RecencyWriter::started);
}

std::unique_ptr<QAbstractTransition> RecencyWriter::transitionToStopped() const
{
	connect(this, & RecencyWriter::collectiveFinished, this, & RecencyWriter::stopped);

	return std::make_unique<QSignalTransition>(this, & RecencyWriter::stopped);
}

std::unique_ptr<QAbstractTransition> RecencyWriter::transitionToBroken() const
{
	connect(& m->dbCollective, & internal::RecencyCollective::errored, this, & RecencyWriter::broke);

	return std::make_unique<QSignalTransition>(this, & RecencyWriter::broke);
}

std::unique_ptr<QAbstractTransition> RecencyWriter::transitionToYielding() const
{
	return std::make_unique<QSignalTransition>(& m->updateTimer, & QTimer::timeout);
}

std::unique_ptr<QAbstractTransition> RecencyWriter::transitionToIdling() const
{
	return std::make_unique<QSignalTransition>(this, & RecencyWriter::collectiveFinished);
}

void RecencyWriter::updateValues()
{
	internal::RecencyCollective::TuplesContainer tuples;
	for (TagValueContainer::const_iterator it = values().begin(); it != values().end(); ++it)
		tuples[(*it)->name()] = internal::RecencyCollective::Tuple{(*it)->value(), QDateTime::currentDateTimeUtc()};

	CUTEHMI_DEBUG("Requesting database handler to update values in the database.");

	if (schema())
		m->dbCollective.update(tuples);
	else
		CUTEHMI_CRITICAL("Schema is not set for '" << this << "' object.");
}

std::unique_ptr<services::Serviceable::ServiceStatuses> RecencyWriter::configureStartingOrRepairing(QState * parent)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * startingTimer = new QState(parent);
	statuses->insert(startingTimer, tr("Starting store timer"));
	connect(startingTimer, & QState::entered, this, & RecencyWriter::startUpdateTimer);

	QState * validatingSchema = createValidatingSchemaSate(parent, statuses.get(), startingTimer);

	QState * waitingForDatabase = createWaitingForDatabaseConnectedSate(parent, statuses.get(), validatingSchema);
	parent->setInitialState(waitingForDatabase);

	return statuses;
}

void RecencyWriter::onSchemaChanged()
{
	m->dbCollective.setSchema(schema());
}

void RecencyWriter::startUpdateTimer()
{
	m->updateTimer.start(interval());
	emit updateTimerStarted();
}

void RecencyWriter::stopUpdateTimer()
{
	m->updateTimer.stop();
	emit updateTimerStopped();
}

void RecencyWriter::confirmCollectiveFinished()
{
	if (!m->dbCollective.busy())
		emit collectiveFinished();
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
