#ifndef CUTEHMI_CUTEHMI__SERVICES__1__LIB_INCLUDE_SERVICES_SERVICEREGISTRY_HPP
#define CUTEHMI_CUTEHMI__SERVICES__1__LIB_INCLUDE_SERVICES_SERVICEREGISTRY_HPP

#include "internal/common.hpp"
#include "Service.hpp"

#include <QList>
#include <QObject>
#include <QQmlListProperty>

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API ServiceRegistry:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(QQmlListProperty<cutehmi::services::Service> serviceList READ serviceList NOTIFY serviceListChanged)
		Q_PROPERTY(int started READ started NOTIFY startedChanged)
		Q_PROPERTY(int stopped READ stopped NOTIFY stoppedChanged)

		ServiceRegistry(QObject * parent = 0);

		~ServiceRegistry() override;

		const QQmlListProperty<Service> & serviceList() const;

		int started() const;

		int stopped() const;

		int count() const;

		void add(Service * service);

//		void clear();

	public slots:
		void start();

		void stop();

	signals:
		void ready();

		void serviceListChanged();

		void startedChanged();

		void stoppedChanged();

	protected slots:
		void stateChangeHandler(Service::state_t oldState, Service::state_t newState);

	private:
		typedef QList<Service *> ServicesContainer;

		struct Members {
			ServicesContainer services;
			QQmlListProperty<Service> serviceList;
			int started;
			int stopped;

			Members(QObject * obj);

		};

		void incStarted();

		void decStarted();

		void incStopped();

		void decStopped();

		static int Count(QQmlListProperty<Service> * property);

		static Service * At(QQmlListProperty<Service> * property, int index);

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
