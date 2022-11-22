#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_ABSTRACTSERVICECONTROLLER_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_ABSTRACTSERVICECONTROLLER_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QQmlEngine>

namespace cutehmi {
namespace services {

class AbstractService;

/**
 * Abstract service controller.
 *
 * In general service controller is an object that can do arbitrary things with a service that is managed by it. In practice
 * controller is typically responsible for calling appropriate service slots at particular events or at specific time. A controller
 * object is not bound to a single service, it can manage multiple services.
 */
class CUTEHMI_SERVICES_API AbstractServiceController:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(AbstractServiceController)
		QML_UNCREATABLE("AbstractServiceController is an abstract class")

	public:
		Q_INVOKABLE virtual void subscribe(cutehmi::services::AbstractService * service) = 0;

		Q_INVOKABLE virtual void unsubscribe(cutehmi::services::AbstractService * service) = 0;

	protected:
		explicit AbstractServiceController(QObject * parent = nullptr);
};

}
}

#endif
