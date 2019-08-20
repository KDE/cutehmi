#ifndef INCLUDECUTEHMISERVICESSERVICEMANAGER_HPP
#define INCLUDECUTEHMISERVICESSERVICEMANAGER_HPP

#include "internal/common.hpp"
#include "ServiceListModel.hpp"

#include <cutehmi/Singleton.hpp>

#include <QQueue>
#include <QMultiHash>

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API ServiceManager:
	public QObject,
	public Singleton<ServiceManager>
{
		Q_OBJECT

		friend class Singleton<ServiceManager>;
		friend class Service;

	public:
		static constexpr int INITIAL_MAX_ACTIVE_SERVICES = 1;

		Q_PROPERTY(int maxActiveServices READ maxActiveServices WRITE setMaxActiveServices NOTIFY maxActiveServicesChanged)

		int maxActiveServices() const;

		void setMaxActiveServices(int maxActiveServices);

	public slots:
		void start();

		void stop();

	signals:
		void maxActiveServicesChanged();

	protected:
		explicit ServiceManager(QObject * parent = nullptr);

		void add(Service * service);

		void remove(Service * service);

		void manage(Service * service);

		void leave(Service * service);

	private:
		typedef QQueue<Service *> YieldingServicesContainer;
		typedef QMultiHash<const internal::StateInterface *, QMetaObject::Connection> StateInterfaceConnectionsContainer;

		struct Members {
			int activeServices;
			int maxActiveServices;
			std::unique_ptr<ServiceListModel> services;
			YieldingServicesContainer yieldingServices;
			StateInterfaceConnectionsContainer stateInterfaceConnections;

			Members():
				activeServices(0),
				maxActiveServices(INITIAL_MAX_ACTIVE_SERVICES),
				services(new ServiceListModel)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif // INCLUDECUTEHMISERVICESSERVICEMANAGER_HPP
