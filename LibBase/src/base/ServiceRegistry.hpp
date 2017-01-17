#ifndef CUTEHMI_LIBBASE_SRC_BASE_SERVICEREGISTRY_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_SERVICEREGISTRY_HPP

#include "../platform.hpp"
#include "Service.hpp"

#include <QList>
#include <QObject>
#include <QQmlListProperty>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API ServiceRegistry:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(QQmlListProperty<cutehmi::base::Service> serviceList READ serviceList NOTIFY serviceListChanged)
		Q_PROPERTY(int started READ started NOTIFY startedChanged)
		Q_PROPERTY(int stopped READ stopped NOTIFY stoppedChanged)

		/**
		 * Get instance. Gets a reference to the instance of the singleton class.
		 * @return a reference to the instance of the singleton class.
		 *
		 * @warning destructor will be called on static de-initialization. Beware of
		 * using singleton instance in destructor of some other static object. If
		 * that's unavoidable, assure that singletons or any static objects are
		 * constructed in the reverse order they are going to be destructed.
		 *
		 * @internal utils::Singleton is not being used to prevent inlining of template function and incorporating
		 * static instance into other translation units.
		 */
		static ServiceRegistry & Instance();

		const QQmlListProperty<Service> & serviceList() const;

		int started() const;

		int stopped() const;

		void add(Service * service);

		void clear();

	public slots:
		void start();

		void stop();

	signals:
		void ready();

		void serviceListChanged();

		void startedChanged();

		void stoppedChanged();

	protected:
		ServiceRegistry(QObject * parent = 0);

		~ServiceRegistry() override;

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

		std::unique_ptr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
