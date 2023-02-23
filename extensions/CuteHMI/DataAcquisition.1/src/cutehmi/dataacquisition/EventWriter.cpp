#include "EventWriter.hpp"

namespace cutehmi {
namespace dataacquisition {

EventWriter::EventWriter(QObject * parent):
	AbstractWriter(parent),
	m(new Members)
{
	connect(this, & AbstractWriter::schemaChanged, this, & EventWriter::onSchemaChanged);
	connect(& m->dbCollective, & internal::EventCollective::busyChanged, this, & EventWriter::confirmCollectiveFinished);
}

void EventWriter::configureStarting(QState * starting, AssignStatusFunction assignStatus)
{
	configureStartingOrRepairing(starting, assignStatus);
}

void EventWriter::configureStarted(QState * active, const QState * idling, const QState * yielding, AssignStatusFunction assignStatus)
{
	Q_UNUSED(yielding)
	Q_UNUSED(idling)

	QState * receivingEvents = new QState(active);
	active->setInitialState(receivingEvents);
	assignStatus(*receivingEvents, tr("Listening for events"));

	connect(receivingEvents, & QState::entered, this, & EventWriter::connectValueChangedSignals);
	connect(receivingEvents, & QState::exited, this, & EventWriter::disconnectValueChangedSignals);
}

void EventWriter::configureStopping(QState * stopping, AssignStatusFunction assignStatus)
{
	QState * waitingForWorkers = new QState(stopping);
	stopping->setInitialState(waitingForWorkers);
	assignStatus(*waitingForWorkers, tr("Waiting for database workers to finish"));
	connect(waitingForWorkers, & QState::entered, this, & EventWriter::confirmCollectiveFinished);
}

void EventWriter::configureBroken(QState * broken, AssignStatusFunction assignStatus)
{
	Q_UNUSED(broken)
	Q_UNUSED(assignStatus)
}

void EventWriter::configureRepairing(QState * repairing, AssignStatusFunction assignStatus)
{
	configureStartingOrRepairing(repairing, assignStatus);
}

void EventWriter::configureEvacuating(QState * evacuating, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	connect(evacuating, & QState::entered, this, & EventWriter::stopped);
}

std::unique_ptr<QAbstractTransition> EventWriter::transitionToStarted() const
{
	connect(this, & EventWriter::schemaValidated, this, & EventWriter::started);

	return std::make_unique<QSignalTransition>(this, & EventWriter::started);
}

std::unique_ptr<QAbstractTransition> EventWriter::transitionToStopped() const
{
	connect(this, & EventWriter::collectiveFinished, this, & EventWriter::stopped);

	return std::make_unique<QSignalTransition>(this, & EventWriter::stopped);
}

std::unique_ptr<QAbstractTransition> EventWriter::transitionToBroken() const
{
	connect(& m->dbCollective, & internal::EventCollective::errored, this, & EventWriter::broke);

	return std::make_unique<QSignalTransition>(this, & EventWriter::broke);
}

std::unique_ptr<QAbstractTransition> EventWriter::transitionToYielding() const
{
	return nullptr;
}

std::unique_ptr<QAbstractTransition> EventWriter::transitionToIdling() const
{
	return nullptr;
}

void EventWriter::onValueAppend(TagValue * tagValue)
{
	if (m->valueChangedConnectionsActive)
		connectValueChangedSignal(tagValue);
	CUTEHMI_DEBUG("Source of values tagged '" << tagValue->name() << "' appended to event writer.");
}

void EventWriter::onValueRemove(TagValue * tagValue)
{
	if (m->valueChangedConnectionsActive)
		tagValue->disconnect(this);
	CUTEHMI_DEBUG("Source of values tagged '" << tagValue->name() << "' removed from event writer.");
}

void EventWriter::onSchemaChanged()
{
	m->dbCollective.setSchema(schema());
}

void EventWriter::insertEvent(TagValue * tagValue)
{
	CUTEHMI_DEBUG("Requesting database handler to insert values into database.");

	if (schema())
		m->dbCollective.insert(*tagValue);
	else
		CUTEHMI_CRITICAL("Schema is not set for '" << this << "' object.");
}

void EventWriter::connectValueChangedSignals()
{
	for (TagValueContainer::const_iterator it = values().begin(); it != values().end(); ++it)
		connectValueChangedSignal(*it);
	m->valueChangedConnectionsActive = true;
}

void EventWriter::disconnectValueChangedSignals()
{
	for (TagValueContainer::const_iterator it = values().begin(); it != values().end(); ++it)
		(*it)->disconnect(this);
	m->valueChangedConnectionsActive = false;
}

void EventWriter::confirmCollectiveFinished()
{
	if (!m->dbCollective.busy())
		emit collectiveFinished();
}

void EventWriter::configureStartingOrRepairing(QState * parent, AssignStatusFunction assignStatus)
{
	QState * validatingSchema = createValidatingSchemaSate(parent,  assignStatus);

	QState * waitingForDatabase = createWaitingForDatabaseConnectedSate(parent, assignStatus, validatingSchema);
	parent->setInitialState(waitingForDatabase);
}

void EventWriter::connectValueChangedSignal(TagValue * value)
{
	QObject::connect(value, & TagValue::valueChanged, this, [value, this]() {
		insertEvent(value);
	});
}

}
}

//(c)C: Copyright © 2022-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
