#include <cutehmi/services/ServiceManager.hpp>

namespace cutehmi {
namespace services {

constexpr int ServiceManager::INITIAL_MAX_ACTIVE_SERVICES;

int ServiceManager::maxActiveServices() const
{
	return m->maxActiveServices;
}

void ServiceManager::setMaxActiveServices(int maxActiveServices)
{
	if (m->maxActiveServices != maxActiveServices) {
		m->maxActiveServices = maxActiveServices;
		emit maxActiveServicesChanged();
	}
}

void ServiceManager::add(Service * service)
{
	m->services->append(service);
}

void ServiceManager::remove(Service * service)
{
	m->services->remove(service);
}

void ServiceManager::manage(Service * service)
{
	QMetaObject::Connection connection;
	if (!service->serviceable().value<Serviceable *>()->transitionToYielding()) {
		connection = QObject::connect(& service->stateInterface()->yielding(), & QState::entered, [service]() {
			service->activate();
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);
	} else {
		connection = QObject::connect(& service->stateInterface()->active(), & QState::exited, [this]() {
			if (m->yieldingServices.empty())
				m->activeServices--;
			else
				m->yieldingServices.dequeue()->activate();
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);

		connection = QObject::connect(& service->stateInterface()->yielding(), & QState::entered, [this, service]() {
			if (m->activeServices < m->maxActiveServices) {
				service->activate();
				m->activeServices++;
			} else
				m->yieldingServices.enqueue(service);
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);

		connection = QObject::connect(& service->stateInterface()->started(), & QState::exited, [this, service]() {
			m->yieldingServices.removeAll(service);
		});
		m->stateInterfaceConnections.insert(service->stateInterface(), connection);
	}
}

void ServiceManager::leave(Service * service)
{
	while (m->stateInterfaceConnections.contains(service->stateInterface()))
		QObject::disconnect(m->stateInterfaceConnections.take(service->stateInterface()));

	if (service->stateInterface()->active().active())
		m->activeServices--;

	m->yieldingServices.removeAll(service);
}

void ServiceManager::start()
{
	for (int i = 0; i < m->services->rowCount(); i++) {
		if (m->services->at(i)->serviceable().value<Serviceable *>())
			m->services->at(i)->start();
	}
}

void ServiceManager::stop()
{
	for (int i = 0; i < m->services->rowCount(); i++)
		if (m->services->at(i)->serviceable().value<Serviceable *>())
			m->services->at(i)->stop();
}

ServiceManager::ServiceManager(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

}
}
