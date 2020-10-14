#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICEMANAGER_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICEMANAGER_HPP

#include "internal/common.hpp"
#include "ServiceListModel.hpp"

#include <cutehmi/Singleton.hpp>

#include <QQueue>
#include <QMultiHash>

namespace cutehmi {
namespace services {

/**
 * %Service manager. %Service manager is a singleton that manages Service objects. Two most important functions are start() and
 * stop() slots, which start and stop services. Services are added to the manager and removed automatically.
 *
 * Activities of services, which are capable of idling and yielding are serialized. Property @ref maxActiveServices controls how
 * many services can be active at the same time.
 */
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

		/**
		  Maximum amount of the services that can be active at the same time.
		  */
		Q_PROPERTY(int maxActiveServices READ maxActiveServices WRITE setMaxActiveServices NOTIFY maxActiveServicesChanged)

		/**
		  Repair interval. Amount of time [ms] that needs to pass before attempting to repair broken service.
		  */
		Q_PROPERTY(int repairInterval READ repairInterval WRITE setRepairInterval NOTIFY repairIntervalChanged)

		/**
		  Amount of running services, that is services which are in any state other than "stopped" state.
		  */
		Q_PROPERTY(int runningCount READ runningCount NOTIFY runningCountChanged)

		/**
		  Services model.
		  */
		Q_PROPERTY(ServiceListModel * model READ model CONSTANT)

		int maxActiveServices() const;

		void setMaxActiveServices(int maxActiveServices);

		int repairInterval() const;

		void setRepairInterval(int repairInterval);

		int runningCount() const;

		ServiceListModel * model() const;

	public slots:
		/**
		 * Start services.
		 */
		void start();

		/**
		 * Stop services.
		 */
		void stop();

	signals:
		void maxActiveServicesChanged();

		void repairIntervalChanged();

		void runningCountChanged();

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
			int runningCount;
			int maxActiveServices;
			int repairInterval;
			std::unique_ptr<ServiceListModel> model;
			YieldingServicesContainer yieldingServices;
			StateInterfaceConnectionsContainer stateInterfaceConnections;	// The only way to disconnect particular lambda from particular emitter is to store its connection.

			Members():
				activeServices(0),
				runningCount(0),
				maxActiveServices(INITIAL_MAX_ACTIVE_SERVICES),
				repairInterval(INITIAL_REPAIR_INTERVAL),
				model(new ServiceListModel)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
