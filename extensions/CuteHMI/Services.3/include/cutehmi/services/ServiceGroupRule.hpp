#ifndef CUTEHMI_SERVICES_SERVICEGROUPRULE_HPP
#define CUTEHMI_SERVICES_SERVICEGROUPRULE_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QQmlEngine>
#include <QAbstractTransition>

namespace cutehmi {
namespace services {

class AbstractService;

class CUTEHMI_SERVICES_API ServiceGroupRule:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(ServiceGroupRule)
		QML_UNCREATABLE("ServiceGroupRule is an abstract class")

	public:
		enum SlotType {
			SERVICE_START,
			SERVICE_STOP,
			SERVICE_ACTIVATE
		};

		virtual std::unique_ptr<QAbstractTransition> conditionalTransition(SlotType type, const AbstractService * service) = 0;

	protected:
		explicit ServiceGroupRule(QObject * parent = nullptr);
};

}
}

#endif
