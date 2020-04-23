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
