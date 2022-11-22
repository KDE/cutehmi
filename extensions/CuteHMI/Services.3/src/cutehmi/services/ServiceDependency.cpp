#include <cutehmi/services/AbstractService.hpp>
#include <cutehmi/services/ServiceDependency.hpp>
#include <cutehmi/services/ServiceGroup.hpp>

namespace cutehmi {
namespace services {

ServiceDependency::ServiceDependency(QObject * parent):
	ServiceGroupRule(parent),
	m(new Members(this))
{
}

void ServiceDependency::setService(AbstractService * service)
{
	if (m->service != service) {
		m->service = service;
		emit serviceChanged();
	}
}

AbstractService * ServiceDependency::service() const
{
	return m->service;
}

QQmlListProperty<AbstractService> ServiceDependency::requiredServiceList()
{
	return m->requiredServiceList;
}

void ServiceDependency::appendRequiredService(AbstractService * service)
{
	RequiredServiceListAppend(& m->requiredServiceList, service);
}

void ServiceDependency::clearRequiredServices()
{
	RequiredServiceListClear(& m->requiredServiceList);
}

std::unique_ptr<QAbstractTransition> ServiceDependency::conditionalTransition(SlotType type, const AbstractService * service)
{
	switch (type) {
		case SERVICE_START:
			if (service == m->service)
				return std::unique_ptr<QAbstractTransition>(new StartConditionTransition(this));
			break;
		case SERVICE_STOP:
			if (m->requiredServices.contains(const_cast<AbstractService *>(service)))
				return std::unique_ptr<QAbstractTransition>(new StopConditionTransition(this));
			break;
		default:
			return nullptr;
	}

	return nullptr;
}

const ServiceDependency::RequiredServicesContainer & ServiceDependency::requiredServices() const
{
	return m->requiredServices;
}

ServiceDependency::RequiredServicesContainer & ServiceDependency::requiredServices()
{
	return m->requiredServices;
}

workarounds::qt5compatibility::sizeType ServiceDependency::RequiredServiceListCount(QQmlListProperty<AbstractService> * property)
{
	return static_cast<RequiredServicesContainer *>(property->data)->count();
}

AbstractService * ServiceDependency::RequiredServiceListAt(QQmlListProperty<AbstractService> * property, workarounds::qt5compatibility::sizeType index)
{
	return static_cast<RequiredServicesContainer *>(property->data)->value(index);
}

void ServiceDependency::RequiredServiceListClear(QQmlListProperty<AbstractService> * property)
{
	static_cast<RequiredServicesContainer *>(property->data)->clear();
}

void ServiceDependency::RequiredServiceListAppend(QQmlListProperty<AbstractService> * property, AbstractService * value)
{
	static_cast<RequiredServicesContainer *>(property->data)->append(value);
}

ServiceDependency::StartConditionTransition::StartConditionTransition(QPointer<ServiceDependency> serviceDependency):
	m(new Members{
	serviceDependency,
	{}})
{
	if (m->serviceDependency)
		for (auto && requiredService : m->serviceDependency->requiredServices())
			connect(requiredService->states(), & StateInterface::startedChanged, this, [this]() {
			reconnectStateEntered();
		});
	reconnectStateEntered();
}

bool ServiceDependency::StartConditionTransition::test() const
{
	if (m->serviceDependency)
		for (auto && requiredService : m->serviceDependency->requiredServices())
			if (!requiredService->states()->started()->active())
				return false;

	return true;
}

bool ServiceDependency::StartConditionTransition::eventTest(QEvent * event)
{
	if (event->type() == static_cast<QEvent::Type>(ServiceGroup::CONDITION_CHECK_EVENT))
		return test();

	return QSignalTransition::event(event);
}

void ServiceDependency::StartConditionTransition::reconnectStateEntered()
{
	for (auto && connection : m->stateEnteredConnections)
		disconnect(connection);

	if (m->serviceDependency)
		for (auto && requiredService : m->serviceDependency->requiredServices()) {
			auto connection = connect(requiredService->states()->started(), & QState::entered, this, [this]() {
				ServiceGroup::PostConditionCheckEvent(machine());
			});
			m->stateEnteredConnections.append(connection);
		}
}

ServiceDependency::StopConditionTransition::StopConditionTransition(QPointer<ServiceDependency> serviceDependency):
	m(new Members{
	serviceDependency,
	{},
	{}})
{
	if (m->serviceDependency) {
		connect(m->serviceDependency->service()->states(), & StateInterface::stoppedChanged, this, [this]() {
			reconnectStateEntered();
		});
		connect(m->serviceDependency->service()->states(), & StateInterface::interruptedChanged, this, [this]() {
			reconnectStateEntered();
		});
	}
	reconnectStateEntered();
}

bool ServiceDependency::StopConditionTransition::test() const
{
	if (m->serviceDependency)
		return m->serviceDependency->service()->states()->stopped()->active()
				|| m->serviceDependency->service()->states()->interrupted()->active();

	return true;
}

bool ServiceDependency::StopConditionTransition::eventTest(QEvent * event)
{
	if (event->type() == static_cast<QEvent::Type>(ServiceGroup::CONDITION_CHECK_EVENT))
		return test();

	return QSignalTransition::event(event);
}

void ServiceDependency::StopConditionTransition::reconnectStateEntered()
{
	disconnect(m->stoppedEnteredConnection);
	disconnect(m->interruptedEnteredConnection);

	if (m->serviceDependency) {
		m->stoppedEnteredConnection = connect(m->serviceDependency->service()->states()->stopped(), & QState::entered, this, [this]() {
			ServiceGroup::PostConditionCheckEvent(machine());
		});
		m->interruptedEnteredConnection = connect(m->serviceDependency->service()->states()->interrupted(), & QState::entered, this, [this]() {
			ServiceGroup::PostConditionCheckEvent(machine());
		});
	}
}

}
}
