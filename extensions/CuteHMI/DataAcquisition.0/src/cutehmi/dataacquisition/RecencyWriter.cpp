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
	connect(waitingForWorkers, & QState::entered, & m->dbCollective, & internal::RecencyCollective::confirmWorkersFinished);

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
	connect(& m->dbCollective, & internal::RecencyCollective::workersFinished, this, & RecencyWriter::stopped);

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
	return std::make_unique<QSignalTransition>(& m->dbCollective, & internal::RecencyCollective::workersFinished);
}

void RecencyWriter::updateValues()
{
	internal::RecencyTable<int>::TuplesContainer intTuples;
	internal::RecencyTable<bool>::TuplesContainer boolTuples;
	internal::RecencyTable<double>::TuplesContainer realTuples;

	for (TagValueContainer::const_iterator it = values().begin(); it != values().end(); ++it) {
		switch ((*it)->value().type()) {
			case QVariant::Int:
				intTuples[(*it)->name()] = internal::RecencyTable<int>::Tuple{(*it)->value().toInt(), QDateTime::currentDateTimeUtc()};
				break;
			case QVariant::Bool:
				boolTuples[(*it)->name()] = internal::RecencyTable<bool>::Tuple{(*it)->value().toBool(), QDateTime::currentDateTimeUtc()};
				break;
			case QVariant::Double:
				realTuples[(*it)->name()] = internal::RecencyTable<double>::Tuple{(*it)->value().toDouble(), QDateTime::currentDateTimeUtc()};
				break;
			default:
				CUTEHMI_CRITICAL("Unsupported type ('" << (*it)->value().typeName() << "') provided as a 'value' of 'TagValue' object.");
		}
	}

	CUTEHMI_DEBUG("Requesting database handler to update values in the database.");

	if (!schema()->name().isNull()) {
		m->dbCollective.update(intTuples);
		m->dbCollective.update(boolTuples);
		m->dbCollective.update(realTuples);
	} else
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

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
