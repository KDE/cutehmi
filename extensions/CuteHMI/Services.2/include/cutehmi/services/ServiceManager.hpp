#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICEMANAGER_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICEMANAGER_HPP

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
		static constexpr int INITIAL_REPAIR_INTERVAL = 10000;

		Q_PROPERTY(int maxActiveServices READ maxActiveServices WRITE setMaxActiveServices NOTIFY maxActiveServicesChanged)
		Q_PROPERTY(int repairInterval READ repairInterval WRITE setRepairInterval NOTIFY repairIntervalChanged)

		int maxActiveServices() const;

		void setMaxActiveServices(int maxActiveServices);

		int repairInterval() const;

		void setRepairInterval(int repairInterval);

	public slots:
		void start();

		void stop();

	signals:
		void maxActiveServicesChanged();

		void repairIntervalChanged();

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
			int repairInterval;
			std::unique_ptr<ServiceListModel> services;
			YieldingServicesContainer yieldingServices;
			StateInterfaceConnectionsContainer stateInterfaceConnections;	// The only way to disconnect particular lambda from particular emitter is to store its connection.

			Members():
				activeServices(0),
				maxActiveServices(INITIAL_MAX_ACTIVE_SERVICES),
				repairInterval(INITIAL_REPAIR_INTERVAL),
				services(new ServiceListModel)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
