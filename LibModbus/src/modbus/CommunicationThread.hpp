#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_COMMUNICATIONTHREAD_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_COMMUNICATIONTHREAD_HPP

#include <QThread>

namespace cutehmi {
namespace modbus {

class Client;

class CommunicationThread:
	public QThread
{
	Q_OBJECT
	typedef QThread Parent;

	public:
		explicit CommunicationThread(Client * client);

	public:
		void run() override;

	public slots:
		void start();

		void stop();

	private:
		bool m_run;
		Client * m_client;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
