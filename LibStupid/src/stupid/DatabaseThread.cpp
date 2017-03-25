#include "../../include/stupid/DatabaseThread.hpp"

#include <QSqlDatabase>
#include <QCoreApplication>
#include <QAbstractEventDispatcher>

namespace cutehmi {
namespace stupid {

DatabaseThread::DatabaseThread()
{
}

QString DatabaseThread::Error::str() const
{
	switch (code()) {
		case Error::NOT_CONFIGURED:
			return tr("Database connection has not been configured.");
		case Error::UNABLE_TO_CONNECT:
			return tr("Unable to open database connection.");
		default:
			return base::Error::str();
	}
}

void DatabaseThread::moveDatabaseConnectionData(std::unique_ptr<stupid::DatabaseConnectionData> dbData)
{
	Q_ASSERT_X(!isRunning(), __FUNCTION__, "altering connection data while database thread is running");

	m_dbData = std::move(dbData);
}

stupid::DatabaseConnectionData * DatabaseThread::dbData() const
{
	return m_dbData.get();
}

void DatabaseThread::run()
{
	m_runLock.lock();
	if (m_dbData) {
		QSqlDatabase db = QSqlDatabase::addDatabase(m_dbData->type, m_dbData->connectionName);
		db.setHostName(m_dbData->hostName);
		db.setPort(m_dbData->port);
		db.setDatabaseName(m_dbData->databaseName);
		db.setUserName(m_dbData->userName);
		db.setPassword(m_dbData->password);
		if (db.open()) {
			CUTEHMI_STUPID_QDEBUG("[TODO provide AppLite with a UI for signaling errors] Connected with database.");
			emit connected();
		} else {
			CUTEHMI_STUPID_QDEBUG("[TODO provide AppLite with a UI for signaling errors] Could not connect with database.");
			emit error(base::errorInfo(Error(Error::UNABLE_TO_CONNECT)));
		}
		exec();
	} else {
		emit (base::errorInfo(Error(Error::NOT_CONFIGURED)));
		exec();
	}
	if (m_dbData) {
		{
			QSqlDatabase db = QSqlDatabase::database(m_dbData->connectionName, false);
			db.close();
		}
		emit disconnected();
		QSqlDatabase::removeDatabase(m_dbData->connectionName);
	}
	m_runLock.unlock();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
