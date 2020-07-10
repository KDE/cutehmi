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
