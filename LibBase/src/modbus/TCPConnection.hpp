#ifndef CUTEHMI_LIBBASE_SRC_MODBUS_TCPCONNECTION_HPP
#define CUTEHMI_LIBBASE_SRC_MODBUS_TCPCONNECTION_HPP

#include "AbstractConnection.hpp"
#include "LibmodbusConnectionTrait.hpp"

#include <modbus.h>

#include <QString>

namespace modbus {

/**
 * TCP connection.
 */
class CUTEHMI_API TCPConnection:
	public AbstractConnection
{
	typedef AbstractConnection Parent;

	public:
		/**
		 * Constructor.
		 * @param node network node IP address (e.g. "127.0.0.1").
		 * @param service service name or port number.
		 */
		TCPConnection(const QString & node, const QString & service = "502");

		virtual ~TCPConnection();

	private:
		QString m_node;
		QString m_service;
};

}

#endif
