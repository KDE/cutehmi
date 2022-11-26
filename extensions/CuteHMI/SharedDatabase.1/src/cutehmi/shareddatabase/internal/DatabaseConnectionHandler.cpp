#include <cutehmi/shareddatabase/internal/DatabaseConnectionHandler.hpp>
#include <cutehmi/shareddatabase/DatabaseWorker.hpp>

#include <QTimer>
#include <QSqlQuery>
#include <QSqlError>

namespace cutehmi {
namespace shareddatabase {
namespace internal {

DatabaseConnectionHandler::DatabaseConnectionHandler(DatabaseConfig config, QObject * parent):
	Parent(parent),
	m(new Members(config))
{
	QObject::connect(this, & DatabaseConnectionHandler::errored, this, & DatabaseConnectionHandler::printError);
}

void DatabaseConnectionHandler::connect()
{
	m->connectionName = m->config.data()->connectionName;
	m->db = QSqlDatabase::addDatabase(m->config.data()->type, m->connectionName);
	m->db.setHostName(m->config.data()->host);
	m->db.setPort(m->config.data()->port);
	m->db.setDatabaseName(m->config.data()->name);
	m->db.setUserName(m->config.data()->user);
	m->db.setPassword(m->config.data()->password);

	if (!m->db.isValid())
		emit errored(CUTEHMI_ERROR(tr("No driver found for database type '%1'.").arg(m->config.data()->type)));
	else {
		if (m->db.open()) {
			CUTEHMI_DEBUG("Connected with database.");
			emit connected(m->connectionName);
		} else {
			emit errored(CUTEHMI_ERROR(tr("Failed to establish connection with database.")));
		}

		m->monitorTimer.start(m->monitorInterval, this);
	}
}

void DatabaseConnectionHandler::disconnect()
{
	m->monitorTimer.stop();
	m->db.close();
	emit disconnected(m->connectionName);
}

void DatabaseConnectionHandler::timerEvent(QTimerEvent * event)
{
	if (event->timerId() == m->monitorTimer.timerId()) {
		m->maintenanceCount += m->monitorInterval;
		if (m->maintenanceCount >= INITIAL_MAINTENANCE_INTERVAL) {
			if (m->db.driverName() == "QPSQL") {
				Notification::Info(tr("Performing database maintenance through connection '%1'.").arg(m->db.connectionName()));

				QSqlQuery query(m->db);
				CUTEHMI_DEBUG("Performing VACUUM...");
				query.exec("VACUUM");
				if (query.lastError().isValid())
					emit errored(CUTEHMI_ERROR(query.lastError().text()));
				else
					CUTEHMI_DEBUG("Query was successful.");
				query.finish();

				CUTEHMI_DEBUG("Performing ANALYZE...");
				query.exec("ANALYZE");
				if (query.lastError().isValid())
					emit errored(CUTEHMI_ERROR(query.lastError().text()));
				else
					CUTEHMI_DEBUG("Query was successful.");
			}
			if (m->db.driverName() == "QSQLITE") {
				Notification::Info(tr("Performing database maintenance through connection '%1'.").arg(m->db.connectionName()));

				QSqlQuery query(m->db);
				CUTEHMI_DEBUG("Performing VACUUM...");
				query.exec("VACUUM");
				if (query.lastError().isValid())
					emit errored(CUTEHMI_ERROR(query.lastError().text()));
				else
					CUTEHMI_DEBUG("Query was successful.");
				query.finish();

				CUTEHMI_DEBUG("Performing ANALYZE...");
				query.exec("ANALYZE");
				if (query.lastError().isValid())
					emit errored(CUTEHMI_ERROR(query.lastError().text()));
				else
					CUTEHMI_DEBUG("Query was successful.");
			}
			m->maintenanceCount = 0;
		}
		if (!m->db.isOpen()) {
			emit errored(CUTEHMI_ERROR(tr("Lost connection with database.")));
			m->maintenanceCount = 0;
		}
	} else
		Parent::timerEvent(event);
}

void DatabaseConnectionHandler::printError(InplaceError error)
{
	CUTEHMI_CRITICAL(error.str());
}

}
}
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
