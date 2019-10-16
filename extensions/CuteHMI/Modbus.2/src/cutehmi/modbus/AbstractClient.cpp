#include <cutehmi/modbus/AbstractClient.hpp>

namespace cutehmi {
namespace modbus {

const services::PollingTimer * AbstractClient::pollingTimer() const
{
	return & m->pollingTimer;
}

services::PollingTimer * AbstractClient::pollingTimer()
{
	return & m->pollingTimer;
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

	connect(idling, & QState::entered, pollingTimer(), & services::PollingTimer::start);

	QState * polling = new QState(active);
	active->setInitialState(polling);
	statuses->insert(polling, tr("Polling"));
	connect(polling, & QState::entered, this, & AbstractClient::poll);

	QState * pollingTask = new QState(polling);
	polling->setInitialState(pollingTask);
	connect(pollingTask, & QState::entered, this, & AbstractClient::pollingTask);

	QState * pollingWait = new QState(polling);
	connect(pollingWait, & QState::entered, pollingTimer()->subtimer(), & services::PollingTimer::start);

	pollingTask->addTransition(this, & AbstractClient::pollingTaskFinished, pollingWait);

	pollingWait->addTransition(pollingTimer()->subtimer(), & services::PollingTimer::triggered, pollingTask);

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
	return std::make_unique<QSignalTransition>(& m->pollingTimer, & services::PollingTimer::triggered);
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
