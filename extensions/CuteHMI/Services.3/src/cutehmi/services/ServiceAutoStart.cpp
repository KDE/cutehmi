#include <cutehmi/services/ServiceAutoStart.hpp>
#include <cutehmi/services/AbstractService.hpp>

namespace cutehmi {
namespace services {

ServiceAutoStart::ServiceAutoStart(QObject * parent):
	AbstractServiceController(parent)
{
}

void ServiceAutoStart::subscribe(AbstractService * service)
{
	connect(service, & AbstractService::initialized, service, & AbstractService::start);
}

void ServiceAutoStart::unsubscribe(AbstractService * service)
{
	disconnect(service, & AbstractService::initialized, service, & AbstractService::start);
}

}
}
