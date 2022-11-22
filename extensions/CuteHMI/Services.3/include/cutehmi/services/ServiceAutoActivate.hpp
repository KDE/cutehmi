#ifndef CUTEHMI_SERVICES_SERVICEAUTOACTIVATE_HPP
#define CUTEHMI_SERVICES_SERVICEAUTOACTIVATE_HPP

#include "internal/common.hpp"

#include "AbstractServiceController.hpp"

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API ServiceAutoActivate:
	public cutehmi::services::AbstractServiceController
{
		Q_OBJECT
		QML_NAMED_ELEMENT(ServiceAutoActivate)

	public:
		ServiceAutoActivate(QObject * parent = nullptr);

		void subscribe(AbstractService * service) override;

		void unsubscribe(AbstractService * service) override;

	private:
		struct ServiceEntry {
			QMetaObject::Connection yieldingEnteredConnection;
			QMetaObject::Connection yieldingChangedConnection;
		};

		typedef QHash<AbstractService *, ServiceEntry> ServiceDataContainer;

		struct Members {
			ServiceDataContainer serviceData;
		};

		MPtr<Members> m;
};

}
}

#endif
