#include <cutehmi/shareddatabase/PostgresMaintenance.hpp>
#include <cutehmi/shareddatabase/Exception.hpp>

namespace cutehmi {
namespace shareddatabase {

PostgresMaintenance::PostgresMaintenance(QObject * parent):
	DataObject(parent)
{
}

void PostgresMaintenance::createDatabase(const QString & name, const QVariantMap & withArgs)
{
	worker([this, name, withArgs](QSqlDatabase & db) {

		bool warning = false;
		bool error = false;

		if (db.driverName() == "QPSQL") {
			QSqlQuery query(db);
			try {
				CUTEHMI_DEBUG("Creating database...");

				QString createArgs = name;
				if (!withArgs.isEmpty()) {
					createArgs.append(" WITH");
					for (auto withIt = withArgs.begin(); withIt != withArgs.end(); ++withIt)
						createArgs.append(" ").append(withIt.key()).append(" = ").append(withIt.value().toString());
				}
				const char * createSQL = R"SQL(
CREATE DATABASE %1;
				)SQL";
				QString queryString = QString(createSQL).arg(createArgs);

				CUTEHMI_DEBUG("SQL query:\n```\n" << queryString + "\n```");
				if (!query.exec(queryString))
					error = true;

				pushError(query.lastError());

				query.finish();
			} catch (const Exception & e) {
				CUTEHMI_CRITICAL(e.what());
				error = true;
			}
		} else {
			emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
			error = true;
		}

		if (error)
			Notification::Critical(tr("Failed to create '%1' database.").arg(name));
		else if (warning)
			Notification::Warning(tr("Created '%1' database although the operation wasn't clean.").arg(name));
		else
			Notification::Info(tr("Created '%1' database.").arg(name));

	})->work();
}

void PostgresMaintenance::dropDatabase(const QString & name)
{
	worker([this, name](QSqlDatabase & db) {

		bool warning = false;
		bool error = false;

		if (db.driverName() == "QPSQL") {
			QSqlQuery query(db);
			try {
				CUTEHMI_DEBUG("Dropping database...");

				const char * dropSQL = R"SQL(
DROP DATABASE %1;
				)SQL";
				QString queryString = QString(dropSQL).arg(name);

				CUTEHMI_DEBUG("SQL query:\n```\n" << queryString + "\n```");
				if (!query.exec(queryString))
					error = true;

				pushError(query.lastError());

				query.finish();
			} catch (const Exception & e) {
				CUTEHMI_CRITICAL(e.what());
				error = true;
			}
		} else {
			emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
			error = true;
		}

		if (error)
			Notification::Critical(tr("Failed to drop '%1' database.").arg(name));
		else if (warning)
			Notification::Warning(tr("Dropped '%1' database although the operation wasn't clean.").arg(name));
		else
			Notification::Info(tr("Dropped '%1' database.").arg(name));

	})->work();
}

}
}
