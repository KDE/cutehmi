#include <cutehmi/services/AbstractService.hpp>

#include <cutehmi/Notification.hpp>
#include <cutehmi/services/AbstractServiceController.hpp>
#include <cutehmi/services/ServiceAutoRepair.hpp>

#include <QCoreApplication>

namespace cutehmi {
namespace services {

constexpr int AbstractService::INITIAL_STOP_TIMEOUT;
constexpr int AbstractService::INITIAL_START_TIMEOUT;
constexpr int AbstractService::INITIAL_REPAIR_TIMEOUT;
constexpr const char * AbstractService::INITIAL_NAME;

AbstractService::~AbstractService()
{
	clearControllers();
}

int AbstractService::stopTimeout() const
{
	return m->stopTimeout;
}

void AbstractService::setStopTimeout(int timeout)
{
	if (m->stopTimeout != timeout) {
		m->stopTimeout = timeout;
		emit stopTimeoutChanged();
	}
}

int AbstractService::startTimeout() const
{
	return m->startTimeout;
}

void AbstractService::setStartTimeout(int startTimeout)
{
	if (m->startTimeout != startTimeout) {
		m->startTimeout = startTimeout;
		emit startTimeoutChanged();
	}
}

int AbstractService::repairTimeout() const
{
	return m->repairTimeout;
}

void AbstractService::setRepairTimeout(int repairTimeout)
{
	if (m->repairTimeout != repairTimeout) {
		m->repairTimeout = repairTimeout;
		emit repairTimeoutChanged();
	}
}

QString AbstractService::name() const
{
	return m->name;
}

void AbstractService::setName(const QString & name)
{
	if (m->name != name) {
		m->name = name;
		emit nameChanged();
	}
}

QString AbstractService::status() const
{
	return m->status;
}

StateInterface * AbstractService::states() const
{
	return m->stateInterface;
}

QQmlListProperty<AbstractServiceController> AbstractService::defaultControllerList()
{
	return m->defaultControllerList;
}

QQmlListProperty<AbstractServiceController> AbstractService::controllerList()
{
	return m->controllerList;
}

void AbstractService::appendController(AbstractServiceController * controller)
{
	ControllerListAppend(& m->controllerList, controller);
}

void AbstractService::clearControllers()
{
	ControllerListClear(& m->controllerList);
}

void AbstractService::start()
{
	emit started();
}

void AbstractService::stop()
{
	emit stopped();
}

void AbstractService::activate()
{
	emit activated();
}

AbstractService::AbstractService(std::unique_ptr<StateInterface> stateInterface, const QString & status, QObject * parent, const ControllersContainer * defaultControllers):
	QObject(parent),
	m(new Members(this, stateInterface.get(), status, defaultControllers))
{
	stateInterface.release()->setParent(this);	// Switch to Qt parent-child memory management.

	for (auto && controller : *defaultControllerListData())
		appendController(controller);
}

const AbstractService::ControllersContainer & AbstractService::DefaultControllers()
{
	static ServiceAutoRepair defaultAutoRepair;
	static ControllersContainer defaultControllers = {& defaultAutoRepair};
	return defaultControllers;
}

const AbstractService::ControllersContainer & AbstractService::controllers() const
{
	return m->controllers;
}

AbstractService::ControllersContainer & AbstractService::controllers()
{
	return m->controllers;
}

void AbstractService::setStatus(const QString & status)
{
	if (m->status != status) {
		m->status = status;
		CUTEHMI_DEBUG(name() << ": " << status);
		emit statusChanged();
	}
}

workarounds::qt5compatibility::sizeType AbstractService::ControllerListCount(QQmlListProperty<AbstractServiceController> * property)
{
	return static_cast<ControllersContainer *>(property->data)->count();
}

AbstractServiceController * AbstractService::ControllerListAt(QQmlListProperty<AbstractServiceController> * property, workarounds::qt5compatibility::sizeType index)
{
	return static_cast<ControllersContainer *>(property->data)->value(index);
}

void AbstractService::ControllerListClear(QQmlListProperty<AbstractServiceController> * property)
{
	ControllersContainer * controllers = static_cast<ControllersContainer *>(property->data);
	AbstractService * service = static_cast<AbstractService *>(property->object);

	for (auto && controller : *controllers)
		controller->unsubscribe(service);

	controllers->clear();
}

void AbstractService::ControllerListAppend(QQmlListProperty<AbstractServiceController> * property, AbstractServiceController * value)
{
	AbstractService * service = static_cast<AbstractService *>(property->object);
	value->subscribe(service);

	static_cast<ControllersContainer *>(property->data)->append(value);
}

workarounds::qt5compatibility::sizeType AbstractService::DefaultControllerListCount(QQmlListProperty<AbstractServiceController> * property)
{
	const ControllersContainer * controllers = static_cast<const ControllersContainer *>(property->data);

	return controllers->count();
}

AbstractServiceController * AbstractService::DefaultControllerListAt(QQmlListProperty<AbstractServiceController> * property, workarounds::qt5compatibility::sizeType index)
{
	const ControllersContainer * controllers = static_cast<const ControllersContainer *>(property->data);

	return controllers->at(index);
}

const AbstractService::ControllersContainer * AbstractService::defaultControllerListData() const
{
	return static_cast<const ControllersContainer *>(m->defaultControllerList.data);
}

}
}
