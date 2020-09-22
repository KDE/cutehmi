#include <cutehmi/dataacquisition/HistoryWriter.hpp>

#include <cutehmi/shareddatabase/Database.hpp>

namespace cutehmi {
namespace dataacquisition {

constexpr int HistoryWriter::INITIAL_INTERVAL;
constexpr int HistoryWriter::INITIAL_SAMPLES;

HistoryWriter::HistoryWriter(QObject * parent):
	AbstractWriter(parent),
	m(new Members)
{
	adjustSamplingTimer();
	connect(this, & AbstractWriter::schemaChanged, this, & HistoryWriter::onSchemaChanged);
	connect(this, & HistoryWriter::intervalChanged, this, & HistoryWriter::adjustSamplingTimer);
	connect(this, & HistoryWriter::samplesChanged, this, & HistoryWriter::adjustSamplingTimer);
	connect(& m->dbCollective, & internal::HistoryCollective::busyChanged, this, & HistoryWriter::confirmCollectiveFinished);
}

int HistoryWriter::interval() const
{
	return m->interval;
}

void HistoryWriter::setInterval(int interval)
{
	CUTEHMI_ASSERT(interval >= 0, "Value of 'interval' property should be non-negative.");

	if (m->interval != interval) {
		m->interval = interval;
		emit intervalChanged();
	}
}

int HistoryWriter::samples() const
{
	return m->samples;
}

void HistoryWriter::setSamples(int samples)
{
	CUTEHMI_ASSERT(samples > 0, "Value of 'samples' property should be greater than zero.");

	if (m->samples != samples) {
		m->samples = samples;
		emit samplesChanged();
	}
}

void HistoryWriter::sampleValues()
{
	CUTEHMI_DEBUG("Sampling values (count: " << m->sampleCounter + 1 << ").");

	for (TagValueContainer::const_iterator it = values().begin(); it != values().end(); ++it) {
		QString tagName = (*it)->name();
		switch ((*it)->value().type()) {
			case QVariant::Int:
				addSample<int>((*it)->value().toInt(), m->tuples[tagName]);
				break;
			case QVariant::Bool:
				addSample<bool>((*it)->value().toBool(), m->tuples[tagName]);
				break;
			case QVariant::Double:
				addSample<double>((*it)->value().toDouble(), m->tuples[tagName]);
				break;
			default:
				CUTEHMI_CRITICAL("Unsupported type ('" << (*it)->value().typeName() << "') provided as a 'value' of 'TagValue' object.");
		}
	}

	m->sampleCounter++;
	if (m->sampleCounter >= samples()) {
		insertValues();
		clearData();
	}
}

void HistoryWriter::insertValues()
{
	CUTEHMI_DEBUG("Requesting database handler to insert values into database.");

	if (schema()) {
		emit insertValuesBegan();
		m->dbCollective.insert(m->tuples);
	} else
		CUTEHMI_CRITICAL("Schema is not set for '" << this << "' object.");
}

void HistoryWriter::onSchemaChanged()
{
	m->dbCollective.setSchema(schema());
}

void HistoryWriter::initialize()
{
	clearData();
	emit initialized();
}

std::unique_ptr<services::Serviceable::ServiceStatuses> HistoryWriter::configureStarting(QState * starting)
{
	return configureStartingOrRepairing(starting);
}

std::unique_ptr<services::Serviceable::ServiceStatuses> HistoryWriter::configureStarted(QState * active, const QState * idling, const QState * yielding)
{
	Q_UNUSED(yielding)
	Q_UNUSED(idling)

	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * inserting = new QState(active);
	statuses->insert(inserting, tr("Inserting values"));

	QState * sampling = new QState(active);
	statuses->insert(sampling, tr("Sampling"));
	active->setInitialState(sampling);

	sampling->addTransition(this, & HistoryWriter::insertValuesBegan, inserting);
	inserting->addTransition(this, & HistoryWriter::collectiveFinished, sampling);

	connect(& m->samplingTimer, & QTimer::timeout, this, & HistoryWriter::sampleValues);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> HistoryWriter::configureStopping(QState * stopping)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * waitingForWorkers = new QState(stopping);
	statuses->insert(waitingForWorkers, tr("Waiting for database workers to finish"));
	connect(waitingForWorkers, & QState::entered, this, & HistoryWriter::confirmCollectiveFinished);

	QState * stoppingTimer = new QState(stopping);
	stopping->setInitialState(stoppingTimer);
	statuses->insert(stoppingTimer, tr("Stopping sampling timer"));
	connect(stoppingTimer, & QState::entered, this, & HistoryWriter::stopSamplingTimer);
	stoppingTimer->addTransition(this, & HistoryWriter::samplingTimerStopped, waitingForWorkers);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> HistoryWriter::configureBroken(QState * broken)
{
	connect(broken, & QState::entered, this, & HistoryWriter::stopSamplingTimer);

	return nullptr;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> HistoryWriter::configureRepairing(QState * repairing)
{
	return configureStartingOrRepairing(repairing);
}

std::unique_ptr<services::Serviceable::ServiceStatuses> HistoryWriter::configureEvacuating(QState * evacuating)
{
	connect(evacuating, & QState::entered, this, & HistoryWriter::stopped);

	return nullptr;
}

std::unique_ptr<QAbstractTransition> HistoryWriter::transitionToStarted() const
{
	connect(this, & HistoryWriter::samplingTimerStarted, this, & HistoryWriter::started);

	return std::make_unique<QSignalTransition>(this, & HistoryWriter::started);
}

std::unique_ptr<QAbstractTransition> HistoryWriter::transitionToStopped() const
{
	connect(this, & HistoryWriter::collectiveFinished, this, & HistoryWriter::stopped);

	return std::make_unique<QSignalTransition>(this, & HistoryWriter::stopped);
}

std::unique_ptr<QAbstractTransition> HistoryWriter::transitionToBroken() const
{
	connect(& m->dbCollective, & internal::HistoryCollective::errored, this, & HistoryWriter::broke);

	return std::make_unique<QSignalTransition>(this, & HistoryWriter::broke);
}

std::unique_ptr<QAbstractTransition> HistoryWriter::transitionToYielding() const
{
	return nullptr;
}

std::unique_ptr<QAbstractTransition> HistoryWriter::transitionToIdling() const
{
	return nullptr;
}

void HistoryWriter::adjustSamplingTimer()
{
	m->samplingTimer.setInterval(interval());
}

void HistoryWriter::startSamplingTimer()
{
	m->samplingTimer.start();
	emit samplingTimerStarted();
}

void HistoryWriter::stopSamplingTimer()
{
	m->samplingTimer.stop();
	emit samplingTimerStopped();
}

void HistoryWriter::confirmCollectiveFinished()
{
	if (!m->dbCollective.busy())
		emit collectiveFinished();
}

std::unique_ptr<services::Serviceable::ServiceStatuses> HistoryWriter::configureStartingOrRepairing(QState * parent)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * startingTimer = new QState(parent);
	statuses->insert(startingTimer, tr("Starting sampling timer"));
	connect(startingTimer, & QState::entered, this, & HistoryWriter::startSamplingTimer);

	QState * validatingSchema = createValidatingSchemaSate(parent, statuses.get(), startingTimer);

	QState * initializing = new QState(parent);
	statuses->insert(initializing, tr("Initializing"));
	connect(initializing, & QState::entered, this, & HistoryWriter::initialize);
	initializing->addTransition(this, & HistoryWriter::initialized, validatingSchema);

	QState * waitingForDatabase = createWaitingForDatabaseConnectedSate(parent, statuses.get(), initializing);
	parent->setInitialState(waitingForDatabase);

	return statuses;
}

void HistoryWriter::clearData()
{
	m->tuples.clear();
	m->sampleCounter = 0;
}

template <typename T>
void HistoryWriter::addSample(T value, internal::HistoryCollective::Tuple & tuple)
{
	if (tuple.count == 0) {
		// Initialize candle.
		tuple.open = value;
		tuple.openTime = QDateTime::currentDateTimeUtc();
		tuple.min = value;
		tuple.max = value;
	} else {
		// Adjust min, max.
		tuple.min = qMin(tuple.min.value<T>(), value);
		tuple.max = qMax(tuple.max.value<T>(), value);
	}

	tuple.closeTime = QDateTime::currentDateTimeUtc();
	tuple.close = value;
	tuple.count++;
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
