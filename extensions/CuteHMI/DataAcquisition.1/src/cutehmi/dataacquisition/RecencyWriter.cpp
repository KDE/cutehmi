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

void RecencyWriter::configureStarting(QState * starting, AssignStatusFunction assignStatus)
{
	configureStartingOrRepairing(starting, assignStatus);
}

void RecencyWriter::configureStarted(QState * active, const QState * idling, const QState * yielding, AssignStatusFunction assignStatus)
{
	Q_UNUSED(yielding)

	connect(idling, & QState::entered, this, & RecencyWriter::startUpdateTimer);

	QState * updating = new QState(active);
	assignStatus(*updating, tr("Updating values"));
	active->setInitialState(updating);
	connect(updating, & QState::entered, this, & RecencyWriter::updateValues);
}

void RecencyWriter::configureStopping(QState * stopping, AssignStatusFunction assignStatus)
{
	QState * waitingForWorkers = new QState(stopping);
	assignStatus(*waitingForWorkers, tr("Waiting for database workers to finish"));
	connect(waitingForWorkers, & QState::entered, this, & RecencyWriter::confirmCollectiveFinished);

	QState * stoppingTimer = new QState(stopping);
	stopping->setInitialState(stoppingTimer);
	assignStatus(*stoppingTimer, tr("Stopping store timer"));
	connect(stoppingTimer, & QState::entered, this, & RecencyWriter::stopUpdateTimer);
	stoppingTimer->addTransition(this, & RecencyWriter::updateTimerStopped, waitingForWorkers);
}

void RecencyWriter::configureBroken(QState * broken, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	connect(broken, & QState::entered, this, & RecencyWriter::stopUpdateTimer);
}

void RecencyWriter::configureRepairing(QState * repairing, AssignStatusFunction assignStatus)
{
	configureStartingOrRepairing(repairing, assignStatus);
}

void RecencyWriter::configureEvacuating(QState * evacuating, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	connect(evacuating, & QState::entered, this, & RecencyWriter::stopped);
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

void RecencyWriter::onValueAppend(TagValue * tagValue)
{
#ifndef CUTEHMI_DEBUG
	Q_UNUSED(tagValue)
#endif
	CUTEHMI_DEBUG("Source of values tagged '" << tagValue->name() << "' appended to recency writer.");
}

void RecencyWriter::onValueRemove(TagValue * tagValue)
{
#ifndef CUTEHMI_DEBUG
	Q_UNUSED(tagValue)
#endif
	CUTEHMI_DEBUG("Source of values tagged '" << tagValue->name() << "' removed from recency writer.");
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

void RecencyWriter::configureStartingOrRepairing(QState * parent, AssignStatusFunction assignStatus)
{
	QState * startingTimer = new QState(parent);
	assignStatus(*startingTimer, tr("Starting store timer"));
	connect(startingTimer, & QState::entered, this, & RecencyWriter::startUpdateTimer);

	QState * validatingSchema = createValidatingSchemaSate(parent, assignStatus, startingTimer);

	QState * waitingForDatabase = createWaitingForDatabaseConnectedSate(parent, assignStatus, validatingSchema);
	parent->setInitialState(waitingForDatabase);
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

//(c)C: Copyright © 2020-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
