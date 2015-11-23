#include "TCPConnection.hpp"
#include "Exception.hpp"

#include <QObject>

namespace modbus {

TCPConnection::TCPConnection(const QString & node, const QString & service):
	m_node(node),
	m_service(service),
	m_connected(false),
	m_context(modbus_new_tcp_pi(node.toLocal8Bit().data(), service.toLocal8Bit().data()))
{
	if (m_context == NULL)
		// %1 network node, %2 service (port).
		throw Exception(QObject::tr("Unable to create modbus connection."), QObject::tr("Unable to create connection for node: %1, service: %2.").arg(m_node).arg(m_service));
}

TCPConnection::~TCPConnection()
{
	if (m_context != NULL)
		modbus_free(m_context);
}

void TCPConnection::connect()
{
	if (m_connected)
		return;
	if (m_context == NULL)
		throw Exception(QObject::tr("Unable to connect."), QObject::tr("Connection has not been properly configured."));
	if (modbus_connect(m_context) == 0)
		m_connected = true;
	else
		// %1 network node, %2 service (port).
		throw Exception(QObject::tr("Unable to connect."), QObject::tr("Unable to connect with the node: %1, service: %2.").arg(m_node).arg(m_service));
}

void TCPConnection::disconnect()
{
	modbus_close(m_context);
	m_connected = false;
}

bool TCPConnection::connected() const
{
	return m_connected;
}

}
