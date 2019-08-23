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

#endif

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
