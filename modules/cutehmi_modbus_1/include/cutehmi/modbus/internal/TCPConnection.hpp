#ifndef H_MODULES_CUTEHMI__MODBUS__1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_TCPCONNECTION_HPP
#define H_MODULES_CUTEHMI__MODBUS__1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_TCPCONNECTION_HPP

#include "common.hpp"
#include "LibmodbusConnection.hpp"

#include <modbus/modbus.h>

#include <QString>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * TCP connection.
 */
class CUTEHMI_MODBUS_API TCPConnection:
	public LibmodbusConnection
{
	typedef LibmodbusConnection Parent;

	public:
		/**
		 * Constructor.
		 * @param node network node IP address (e.g. "127.0.0.1").
		 * @param service service name or port number.
		 * @param unitId unit identifier. This is useful only in bridged sub-networks (like serial communication over TCP/IP).
		 * Bridge device can use this identifier to route traffic to specific modbus device in a sub-network.
		 * Value of "0xff" is recommended as non-significant value (as defined by MODBUS_TCP_SLAVE).
		 *
		 * @throw Exception.
		 */
		TCPConnection(const QString & node = "127.0.0.1", const QString & service = "502", int unitId =  MODBUS_TCP_SLAVE) noexcept(false);

		virtual ~TCPConnection();

		const QString & node() const;

		const QString & service() const;

		int unitId() const;

	private:
		struct Members
		{
			QString node;
			QString service;
			int unitId;
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
