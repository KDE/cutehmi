#include "TCPConnection.hpp"
#include "Exception.hpp"

#include <QObject>

namespace cutehmi {
namespace modbus {

TCPConnection::TCPConnection(const QString & node, const QString & service):
	Parent(modbus_new_tcp_pi(node.toLocal8Bit().data(), service.toLocal8Bit().data())),
	m_node(node),
	m_service(service)
{
	if (context() == NULL)
		// %1 network node, %2 service (port).
		throw Exception(QObject::tr("Unable to create connection for node: %1, service: %2.").arg(m_node).arg(m_service));
}

TCPConnection::~TCPConnection()
{
	modbus_free(context());
}

}
}
