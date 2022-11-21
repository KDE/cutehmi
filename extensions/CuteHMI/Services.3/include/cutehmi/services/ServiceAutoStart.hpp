#ifndef CUTEHMI_SERVICES_SERVICEAUTOSTART_HPP
#define CUTEHMI_SERVICES_SERVICEAUTOSTART_HPP

#include "internal/common.hpp"

#include "AbstractServiceController.hpp"

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API ServiceAutoStart:
	public cutehmi::services::AbstractServiceController
{
		Q_OBJECT
		QML_NAMED_ELEMENT(ServiceAutoStart)

	public:
		ServiceAutoStart(QObject * parent = nullptr);

		void subscribe(AbstractService * service) override;

		void unsubscribe(AbstractService * service) override;
};

}
}

#endif // SERVICEAUTOSTART_HPP
