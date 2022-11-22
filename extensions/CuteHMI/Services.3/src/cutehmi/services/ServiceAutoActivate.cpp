#include <cutehmi/services/ServiceAutoActivate.hpp>
#include <cutehmi/services/AbstractService.hpp>

#include <QAbstractState>

namespace cutehmi {
namespace services {

ServiceAutoActivate::ServiceAutoActivate(QObject * parent):
	AbstractServiceController(parent),
	m(new Members)
{
}

void ServiceAutoActivate::subscribe(AbstractService * service)
{
	if (m->serviceData.contains(service)) {
		CUTEHMI_WARNING("Service " << service << " is already subscribed to " << this << ".");
		return;
	}

	ServiceEntry entry;
	entry.yieldingEnteredConnection = connect(service->states()->startedStates()->yielding(), & QAbstractState::entered, service, & AbstractService::activate);
	entry.yieldingChangedConnection = connect(service->states()->startedStates(), & StartedStateInterface::yieldingChanged, this, [this, service]() {
		CUTEHMI_ASSERT(m->serviceData.contains(service), "serviceData must contain service");
		disconnect(m->serviceData[service].yieldingEnteredConnection);
		m->serviceData[service].yieldingEnteredConnection = connect(service->states()->startedStates()->yielding(), & QAbstractState::entered, service, & AbstractService::activate);
	});
	m->serviceData.insert(service, entry);
}

void ServiceAutoActivate::unsubscribe(AbstractService * service)
{
	if (!m->serviceData.contains(service)) {
		CUTEHMI_WARNING("Can not unsubscribe service " << service << " as it was not subscribed to " << this << ".");
		return;
	}

	auto entry = m->serviceData.take(service);
	disconnect(entry.yieldingEnteredConnection);
	disconnect(entry.yieldingChangedConnection);
}

}
}
