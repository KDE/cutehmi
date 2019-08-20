#include <cutehmi/services/Service.hpp>

#include <cutehmi/services/ServiceManager.hpp>
#include <cutehmi/Notification.hpp>

#include <QCoreApplication>
#include <QThread>

namespace cutehmi {
namespace services {

constexpr int Service::INITIAL_STOP_TIMEOUT;
constexpr const char * Service::INITIAL_NAME;

Service::Service(QObject * parent):
	QObject(parent),
	m(new Members)
{
	ServiceManager::Instance().add(this);
	setStatus(DefaultStatus());
}

Service::~Service()
{
	stop();

	// Wait till either service stops or timeout is reached.
	if (m->stateInterface)
		while (!m->stateInterface->stopped().active() && !m->stateInterface->interrupted().active())
			QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents);

	if (m->serviceable)
		ServiceManager::Instance().leave(this);
	ServiceManager::Instance().remove(this);

	if (m->stateMachine)
		m->stateMachine->stop();
}

int Service::stopTimeout() const
{
	return m->stopTimeout;
}

void Service::setStopTimeout(int timeout)
{
	if (m->stopTimeout != timeout) {
		m->stopTimeout = timeout;
		emit stopTimeoutChanged();
	}
}

QString Service::name() const
{
	return m->name;
}

void Service::setName(const QString & name)
{
	if (m->name != name) {
		m->name = name;
		emit nameChanged();
	}
}

QString Service::status() const
{
	return m->status;
}

void Service::setServiceable(QVariant serviceable)
{
	QObject * qobjectPtr = serviceable.value<QObject *>();
	Serviceable * serviceablePtr = dynamic_cast<Serviceable *>(qobjectPtr);
	if (qobjectPtr != nullptr && serviceablePtr == nullptr)
		CUTEHMI_WARNING("Object assigned as serviceable to '"  << name() << "' service does not implement 'cutehmi::services::Serviceable' interface.");

	if (m->serviceable != serviceablePtr) {
		if (m->serviceable)
			ServiceManager::Instance().leave(this);
		destroyStateMachine();
		if (serviceablePtr)
			initializeStateMachine(*serviceablePtr);
		m->serviceable = serviceablePtr;
		if (m->serviceable)
			ServiceManager::Instance().manage(this);
		else
			setStatus(DefaultStatus());
		emit serviceableChanged();
	}
}

QVariant Service::serviceable() const
{
	return QVariant::fromValue(m->serviceable);
}

void Service::start()
{
	emit started();
}

void Service::stop()
{
	emit stopped();
	if (stopTimeout() >= 0)
		m->timeoutTimer.start(stopTimeout());
}

internal::StateInterface * Service::stateInterface()
{
	return m->stateInterface;
}

const internal::StateInterface * Service::stateInterface() const
{
	return m->stateInterface;
}

void Service::activate()
{
	emit activated();
}

void Service::setStatus(const QString & status)
{
	if (m->status != status) {
		m->status = status;
		emit statusChanged();
	}
}

QString & Service::DefaultStatus()
{
	static QString name = QObject::tr("Unmanaged");
	return name;
}

void Service::destroyStateMachine()
{
	if (m->stateMachine) {
		m->stateMachine->stop();
		m->stateMachine->deleteLater();
		m->stateMachine = nullptr;
		m->stateInterface = nullptr;
	}
}

void Service::initializeStateMachine(Serviceable & serviceable)
{
	try {
		m->stateMachine = new QStateMachine(this);
		m->stateInterface = new internal::StateInterface(m->stateMachine);

		connect(m->stateInterface, & internal::StateInterface::statusChanged, this, [this]() {
			setStatus(m->stateInterface->status());
		} );

		connect(& m->stateInterface->interrupted(), & QState::entered, [this]() {
			Notification::Critical(tr("Interrupting stop sequence of '%1' service, because it took more than %2 [ms].").arg(name()).arg(stopTimeout()));
		});
		connect(& m->stateInterface->started(), & QState::entered, [this]() {
			Notification::Info(tr("Service '%1' has started.").arg(name()));
		});
		connect(& m->stateInterface->stopped(), & QState::entered, [this]() {
			Notification::Info(tr("Service '%1' is stopped.").arg(name()));
		});
		connect(& m->stateInterface->broken(), & QState::entered, [this]() {
			Notification::Warning(tr("Service '%1' broke.").arg(name()));
		});

		m->stateInterface->stopped().assignProperty(m->stateInterface, "status", tr("Stopped"));
		m->stateInterface->interrupted().assignProperty(m->stateInterface, "status", tr("Interrupted"));
		m->stateInterface->starting().assignProperty(m->stateInterface, "status", tr("Starting"));
		m->stateInterface->started().assignProperty(m->stateInterface, "status", tr("Started"));
		m->stateInterface->idling().assignProperty(m->stateInterface, "status", tr("Idling"));
		m->stateInterface->yielding().assignProperty(m->stateInterface, "status", tr("Yielding"));
		m->stateInterface->active().assignProperty(m->stateInterface, "status", tr("Active"));
		m->stateInterface->stopping().assignProperty(m->stateInterface, "status", tr("Stopping"));
		m->stateInterface->broken().assignProperty(m->stateInterface, "status", tr("Broken"));
		m->stateInterface->repairing().assignProperty(m->stateInterface, "status", tr("Repairing"));

		m->stateMachine->addState(& m->stateInterface->stopped());
		m->stateMachine->addState(& m->stateInterface->interrupted());
		m->stateMachine->addState(& m->stateInterface->starting());
		m->stateMachine->addState(& m->stateInterface->started());
		m->stateMachine->addState(& m->stateInterface->stopping());
		m->stateMachine->addState(& m->stateInterface->broken());
		m->stateMachine->addState(& m->stateInterface->repairing());
		m->stateMachine->setInitialState(& m->stateInterface->stopped());

		m->stateInterface->stopped().addTransition(this, & Service::started, & m->stateInterface->starting());
		m->stateInterface->started().addTransition(this, & Service::stopped, & m->stateInterface->stopping());
		m->stateInterface->broken().addTransition(this, & Service::started, & m->stateInterface->repairing());
		m->stateInterface->broken().addTransition(this, & Service::stopped, & m->stateInterface->stopped());
		m->stateInterface->stopping().addTransition(& m->timeoutTimer, & QTimer::timeout, & m->stateInterface->interrupted());
		m->stateInterface->yielding().addTransition(this, & Service::activated, & m->stateInterface->active());

		addTransition(& m->stateInterface->starting(), & m->stateInterface->started(), serviceable.transitionToStarted());
		addTransition(& m->stateInterface->repairing(), & m->stateInterface->started(), serviceable.transitionToStarted());
		addTransition(& m->stateInterface->stopping(), & m->stateInterface->stopped(), serviceable.transitionToStopped());
		addTransition(& m->stateInterface->starting(), & m->stateInterface->broken(), serviceable.transitionToBroken());
		addTransition(& m->stateInterface->started(), & m->stateInterface->broken(), serviceable.transitionToBroken());
		addTransition(& m->stateInterface->repairing(), & m->stateInterface->broken(), serviceable.transitionToBroken());
		if (serviceable.transitionToIdling())
			addTransition(& m->stateInterface->active(), & m->stateInterface->idling(), serviceable.transitionToIdling());
		addTransition(& m->stateInterface->idling(), & m->stateInterface->yielding(), serviceable.transitionToYielding());

		addStatuses(serviceable.configureBroken(& m->stateInterface->broken()));
		addStatuses(serviceable.configureStarted(& m->stateInterface->active(), & m->stateInterface->idling(), & m->stateInterface->yielding()));
		addStatuses(serviceable.configureStarting(& m->stateInterface->starting()));
		addStatuses(serviceable.configureStopping(& m->stateInterface->stopping()));
		addStatuses(serviceable.configureRepairing(& m->stateInterface->repairing()));

		m->stateMachine->start();
		QCoreApplication::processEvents();	// This is required in order to trully start state machine and prevent it from ignoring incomming events.
	} catch (const std::exception & e) {
		CUTEHMI_CRITICAL("Could not initialize new state machine, because of following exception: " << e.what());
	}
}

void Service::addTransition(QState * source, QState * target, std::unique_ptr<QAbstractTransition> transition)
{
	if (transition) {
		transition->setParent(source);
		transition->setTargetState(target);
		source->addTransition(transition.release());
	} else
		source->addTransition(target);
}

void Service::addStatuses(std::unique_ptr<Serviceable::ServiceStatuses> statuses)
{
	if (statuses)
		for (auto stateStatus = statuses->begin(); stateStatus != statuses->end(); ++stateStatus)
			stateStatus.key()->assignProperty(m->stateInterface, "status", stateStatus.value());
}

}
}
