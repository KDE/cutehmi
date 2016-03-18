#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_TCPCONNECTION_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_TCPCONNECTION_HPP

#include "AbstractConnection.hpp"

#include <modbus.h>

#include <QString>

namespace cutehmi {
namespace modbus {

/**
 * TCP connection.
 */
class CUTEHMI_MODBUS_API TCPConnection:
	public AbstractConnection
{
	typedef AbstractConnection Parent;

	public:
		/**
		 * Constructor.
		 * @param node network node IP address (e.g. "127.0.0.1").
		 * @param service service name or port number.
		 *
		 * @throw Exception.
		 */
		TCPConnection(const QString & node = "127.0.0.1", const QString & service = "502");

		virtual ~TCPConnection();

	private:
		QString m_node;
		QString m_service;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
