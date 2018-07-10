#include "../../../../include/cutehmi/modbus/internal/TCPConnection.hpp"
#include "../../../../include/cutehmi/modbus/Exception.hpp"

#include <QObject>

namespace cutehmi {
namespace modbus {
namespace internal {

TCPConnection::TCPConnection(const QString & node, const QString & service, int unitId) noexcept(false):
	Parent(modbus_new_tcp_pi(node.toLocal8Bit().data(), service.toLocal8Bit().data())),
	m(new Members{node, service, unitId})
{
	if (context() == NULL)
		// %1 network node, %2 service (port).
		throw Exception(QObject::tr("Unable to create connection for the node '%1', service '%2'.").arg(m->node).arg(m->service));
	modbus_set_slave(context(), m->unitId);
}

TCPConnection::~TCPConnection()
{
	modbus_free(context());
}

const QString & TCPConnection::node() const
{
	return m->node;
}

const QString & TCPConnection::service() const
{
	return m->service;
}

int TCPConnection::unitId() const
{
	return m->unitId;
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
