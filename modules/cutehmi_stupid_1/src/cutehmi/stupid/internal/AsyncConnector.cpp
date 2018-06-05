#include "../../../../include/cutehmi/stupid/internal/AsyncConnector.hpp"

#include <QSqlQuery>

namespace cutehmi {
namespace stupid {
namespace internal {

AsyncConnector::AsyncConnector(DatabaseThread * dbThread, QObject * parent):
	QObject(parent),
	m_dbThread(dbThread),
	m_daemonSleep(0),
	m_status(INIT)
{
	m_dbWorker.employ(*m_dbThread, false);
	QObject::connect(m_dbThread, & DatabaseThread::connected, this, & AsyncConnector::connect);
	QObject::connect(& m_dbWorker, & Worker::ready, this, & AsyncConnector::connect);
}

const QStringList & AsyncConnector::w1Ids() const
{
	return m_w1Ids;
}

unsigned long AsyncConnector::daemonSleep() const
{
	return m_daemonSleep;
}

AsyncConnector::Status AsyncConnector::status() const
{
	return m_status;
}

void AsyncConnector::connect()
{
	switch (m_status) {
		case INIT:
			CUTEHMI_LOG_DEBUG("Establishing connection - 'INIT'.");
			m_status= ENUMERATE_DEVICES;
		case ENUMERATE_DEVICES:
			CUTEHMI_LOG_DEBUG("Establishing connection - 'ENUMERATE_DEVICES'.");
			// For proper thread affinity of DS18B20* objects do not create them inside m_dbThread, just store the results of a query.
			m_dbWorker.setTask([this]() {
				QSqlQuery query(QSqlDatabase::database(m_dbThread->dbData()->connectionName, false));
				query.exec("SELECT w1_device.w1_id "
						   "FROM ds18b20 INNER JOIN w1_device ON ds18b20.w1_device_id = w1_device.id");
				while (query.next())
					m_w1Ids.append(query.value(0).toString());
			});
			m_status= LOAD_DAEMON_SLEEP;
			m_dbWorker.work();
			break;
		case LOAD_DAEMON_SLEEP:
			CUTEHMI_LOG_DEBUG("Establishing connection - 'LOAD_DAEMON_SLEEP'.");
			m_dbWorker.setTask([this]() {
				QSqlQuery query(QSqlDatabase::database(m_dbThread->dbData()->connectionName, false));
				query.exec("SELECT daemon_sleep FROM settings");
				while (query.next())
					m_daemonSleep = query.value(0).toLongLong();
			});
			m_status= FINALIZE;
			m_dbWorker.work();
			break;
		case FINALIZE:
			CUTEHMI_LOG_DEBUG("Establishing connection - 'FINALIZE'.");
			m_status= CONNECTED;
			emit connected(this);
			break;
		case CONNECTED:
			CUTEHMI_LOG_WARNING("Received signal, but connection status is already 'CONNECTED'.");
			break;
		default:
			qFatal("Unrecognized connection status code: '%d'.", static_cast<int>(m_status));
			break;
	}

}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
