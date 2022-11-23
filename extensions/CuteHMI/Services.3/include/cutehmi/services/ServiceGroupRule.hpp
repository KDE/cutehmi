#ifndef CUTEHMI_SERVICES_SERVICEGROUPRULE_HPP
#define CUTEHMI_SERVICES_SERVICEGROUPRULE_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QQmlEngine>
#include <QAbstractTransition>

namespace cutehmi {
namespace services {

class AbstractService;

/**
 * %Service group rule.
 *
 * %Service group rules are applied by ServiceGroup to customize the process of starting, stopping or activating the services.
 * Internally for each @ref AbstractService "service" in the group a substate is created in the ServiceGroup state configured via
 * Serviceable interface (such as starting, stopping, repairing, active). %Service group will then query its ServiceGroupRule
 * objects by calling conditionalTransition() function. If confitionalTransition() returns non-null value, then additional,
 * subsequent substate is prepended and the returned transition object is used to define the transition between them.
 */
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

		/**
		 * Get conditional transition that should be applied to a particular service and slot type.
		 * @param type slot type. States to which the transtion should be applied are defined by slot type. Enum values correspond to
		 * AbstractService::start(), AbstractService::stop() and AbstractService::activate() slots. See the
		 * @ref cutehmi-services-state-interface-diagram "state interface diagram" to determine, which states are activated by
		 * signals related to these slots (signals are named using past perfect verbs i.e.: start - started, stop - stopped,
		 * activate - activated). The transition will be applied to a newly created substate for the the relevant, existing substate
		 * dedicated for a particular @a service.
		 * @param service service belonging to the group for which the transition might be potentially applied.
		 * @return transition object or @p nullptr if no transition shall be applied to a particular @a service and state related to
		 * a particular slot @a type.
		 */
		virtual std::unique_ptr<QAbstractTransition> conditionalTransition(SlotType type, const AbstractService * service) = 0;

	protected:
		explicit ServiceGroupRule(QObject * parent = nullptr);
};

}
}

#endif
