#ifndef CUTEHMI_LIBBASE_SRC_BASE_SERVICES_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_SERVICES_HPP

#include "../platform.hpp"

#include <QList>
#include <QObject>

namespace cutehmi {
namespace base {

class IService;

class CUTEHMI_BASE_API Services:
	public QObject
{
	Q_OBJECT

	public:
		void add(IService * runner);

		void clear();

	public slots:
		void start();

		void stop();

	private:
		typedef QList<IService *> ServicesContainer;

		ServicesContainer m_services;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
