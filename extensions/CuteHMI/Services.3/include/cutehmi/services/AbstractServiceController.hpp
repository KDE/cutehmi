#ifndef CUTEHMI_SERVICES_ABSTRACTSERVICECONTROLLER_HPP
#define CUTEHMI_SERVICES_ABSTRACTSERVICECONTROLLER_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QQmlEngine>

namespace cutehmi {
namespace services {

class AbstractService;

class CUTEHMI_SERVICES_API AbstractServiceController:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(AbstractServiceController)
		QML_UNCREATABLE("AbstractServiceController is an abstract class")

	public:
		virtual void subscribe(AbstractService * service) = 0;

		virtual void unsubscribe(AbstractService * service) = 0;

	protected:
		explicit AbstractServiceController(QObject * parent = nullptr);
};

}
}

#endif
