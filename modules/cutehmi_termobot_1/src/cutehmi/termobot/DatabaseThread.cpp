#include "DatabaseThread.hpp"

#include <QSqlDatabase>
#include <QCoreApplication>
#include <QAbstractEventDispatcher>

namespace cutehmi {
namespace termobot {

DatabaseThread::DatabaseThread(std::unique_ptr<DatabaseConnectionData> dbData):
    m(new Members)
{
	m->dbData = std::move(dbData);
}

QString DatabaseThread::Error::str() const
{
    switch (code()) {
        case Error::NOT_CONFIGURED:
            return tr("Database connection has not been configured.");
        case Error::UNABLE_TO_CONNECT:
            return tr("Unable to establish database connection.");
        default:
            return Error::str();
    }
}

DatabaseConnectionData * DatabaseThread::dbData() const
{
    return m->dbData.get();
}

void DatabaseThread::run()
{
    QMutexLocker locker(& m->runLock);

	if (m->dbData) {
		QSqlDatabase db = QSqlDatabase::addDatabase(m->dbData->type, m->dbData->connectionName);
        db.setHostName(m->dbData->hostName);
        db.setPort(m->dbData->port);
        db.setDatabaseName(m->dbData->databaseName);
        db.setUserName(m->dbData->userName);
        db.setPassword(m->dbData->password);
        if (db.open()) {
            CUTEHMI_LOG_DEBUG("[TODO provide App with a UI for signaling errors] Connected with database.");
            emit connected();
        } else {
            CUTEHMI_LOG_DEBUG("[TODO provide App with a UI for signaling errors] Could not connect with database.");
            emit error(errorInfo(Error(Error::UNABLE_TO_CONNECT)));
        }
        exec();
    } else {
        emit (errorInfo(Error(Error::NOT_CONFIGURED)));
        exec();
    }
    if (m->dbData) {
        {
            QSqlDatabase db = QSqlDatabase::database(m->dbData->connectionName, false);
            db.close();
        }
        emit disconnected();
        QSqlDatabase::removeDatabase(m->dbData->connectionName);
    }
}

}
}

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
