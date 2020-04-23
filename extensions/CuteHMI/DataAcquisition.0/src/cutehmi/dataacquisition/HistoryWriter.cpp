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
		switch ((*it)->value().type()) {
			case QVariant::Int:
				addIntSample((*it)->name(), (*it)->value().toInt());
				break;
			case QVariant::Bool:
				addBoolSample((*it)->name(), (*it)->value().toInt());
				break;
			case QVariant::Double:
				addRealSample((*it)->name(), (*it)->value().toInt());
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

	if (!schema()->name().isNull()) {
		emit insertValuesBegan();
		m->dbCollective.insert(m->intTuples);
		m->dbCollective.insert(m->boolTuples);
		m->dbCollective.insert(m->realTuples);
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
	inserting->addTransition(& m->dbCollective, & internal::HistoryCollective::workersFinished, sampling);

	connect(& m->samplingTimer, & QTimer::timeout, this, & HistoryWriter::sampleValues);

	return statuses;
}

std::unique_ptr<services::Serviceable::ServiceStatuses> HistoryWriter::configureStopping(QState * stopping)
{
	std::unique_ptr<services::Serviceable::ServiceStatuses> statuses = std::make_unique<services::Serviceable::ServiceStatuses>();

	QState * waitingForWorkers = new QState(stopping);
	statuses->insert(waitingForWorkers, tr("Waiting for database workers to finish"));
	connect(waitingForWorkers, & QState::entered, & m->dbCollective, & internal::HistoryCollective::confirmWorkersFinished);

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
	connect(& m->dbCollective, & internal::HistoryCollective::workersFinished, this, & HistoryWriter::stopped);

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

void HistoryWriter::addIntSample(const QString & tagName, int value)
{
	addSample(value, m->intTuples[tagName]);
}

void HistoryWriter::addBoolSample(const QString & tagName, bool value)
{
	addSample(value, m->boolTuples[tagName]);
}

void HistoryWriter::addRealSample(const QString & tagName, double value)
{
	addSample(value, m->realTuples[tagName]);
}

void HistoryWriter::clearData()
{
	m->intTuples.clear();
	m->boolTuples.clear();
	m->realTuples.clear();
	m->sampleCounter = 0;
}

template <typename T>
void HistoryWriter::addSample(T value, typename internal::HistoryTable<T>::Tuple & tuple)
{
	if (tuple.count == 0) {
		// Initialize candle.
		tuple.open = value;
		tuple.openTime = QDateTime::currentDateTimeUtc();
	}

	tuple.closeTime = QDateTime::currentDateTimeUtc();
	tuple.close = value;
	tuple.min = qMin(tuple.min, value);
	tuple.max = qMax(tuple.max, value);
	tuple.count++;
}

}
}

