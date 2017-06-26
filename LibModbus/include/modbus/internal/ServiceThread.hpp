#ifndef CUTEHMI_LIBMODBUS_INCLUDE_MODBUS_INTERNAL_SERVICETHREAD_HPP
#define CUTEHMI_LIBMODBUS_INCLUDE_MODBUS_INTERNAL_SERVICETHREAD_HPP

#include "common.hpp"

#include <QThread>
#include <QAtomicInt>

namespace cutehmi {
namespace modbus {

class Client;

namespace internal {

class ServiceThread:
	public QThread
{
	Q_OBJECT
	typedef QThread Parent;

	public:
		explicit ServiceThread(Client * client);

	public:
		unsigned long sleep() const;

		void setSleep(unsigned long sleep);

		void run() override;

	signals:
		void ran();

	public slots:
		void start();

		void stop();

	private:
		QAtomicInt m_run;
		unsigned long m_sleep;
		Client * m_client;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
