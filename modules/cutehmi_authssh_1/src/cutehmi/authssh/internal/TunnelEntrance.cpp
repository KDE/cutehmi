#include "../../../../include/cutehmi/authssh/internal/TunnelEntrance.hpp"

#include <QTcpSocket>

namespace cutehmi {
namespace authssh {
namespace internal {

TunnelEntrance::TunnelEntrance(const QHostAddress & host, uint port, QObject * parent):
	QObject(parent),
	m(new Members(host, port))
{
	connect(m->tcpServer, & QTcpServer::newConnection, this, & TunnelEntrance::establishConnection);
	m->tcpServer->setMaxPendingConnections(1);
}

TunnelEntrance::~TunnelEntrance()
{
	close();
}

qint64 TunnelEntrance::bytesAvailable() const
{
	return m->data.size();
}

int TunnelEntrance::read(QByteArray & data)
{
	int n = m->data.size();
	data += m->data;
	m->data.clear();
	return n;
}

qint64 TunnelEntrance::write(const QByteArray & data)
{
	if (m->connection)
		return m->connection->write(data);
	return 0;
}

bool TunnelEntrance::open()
{
	CUTEHMI_LOG_DEBUG("Opening tunnel entrance.");

	return m->tcpServer->listen(m->host, m->port);
}

void TunnelEntrance::close()
{
	CUTEHMI_LOG_DEBUG("Closing tunnel entrance.");

	m->tcpServer->close();
	if (m->connection)
		m->connection->disconnectFromHost();
}

void TunnelEntrance::establishConnection()
{	
	if (m->tcpServer) {
		CUTEHMI_LOG_DEBUG("Establishing connection via tunnel.");

		m->tcpServer->pauseAccepting();
		m->connection = m->tcpServer->nextPendingConnection();
		connect(m->connection, & QAbstractSocket::disconnected, this, & TunnelEntrance::removeConnection);
		connect(m->connection, & QAbstractSocket::readyRead, this, & TunnelEntrance::readData);
	}
}

void TunnelEntrance::removeConnection()
{
	CUTEHMI_LOG_DEBUG("Removing tunnel connection.");

	if (m->connection) {
		m->connection->deleteLater();
		m->connection = nullptr;
	}
	if (m->tcpServer && m->tcpServer->isListening())
		m->tcpServer->resumeAccepting();
}

void TunnelEntrance::readData()
{
	if (m->connection)
		m->data += m->connection->readAll();
	emit readyRead();
}

}
}
}

//(c)MPWZ: Copyright © 2018, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
