#include <cutehmi/dataacquisition/DataObject.hpp>

#include <QMutexLocker>

namespace cutehmi {
namespace dataacquisition {

DataObject::DataObject(QObject * parent):
	QObject(parent),
	m(new Members)
{
	connect(this, & DataObject::errored, this, & DataObject::printError);
}

QString DataObject::connectionName() const
{
	return m->connectionName;
}

void DataObject::setConnectionName(const QString & connectionName)
{
	if (m->connectionName != connectionName) {
		m->connectionName = connectionName;
		emit connectionNameChanged();
	}
}

void DataObject::resetConnectionName()
{
	m->connectionName.clear();
}

bool DataObject::busy() const
{
	return m->busy != 0;
}

void DataObject::pushError(const QSqlError & sqlError)
{
	QMutexLocker locker(& m->sqlErrorsMutex);
	m->sqlErrors.append(sqlError);
}

shareddatabase::DatabaseWorker * DataObject::worker(std::function<void (QSqlDatabase & db)> task) const
{
	std::unique_ptr<shareddatabase::DatabaseWorker> databaseWorker(new shareddatabase::DatabaseWorker(m->connectionName, task));
	connect(databaseWorker.get(), & shareddatabase::DatabaseWorker::ready, this, & DataObject::processErrors);
	connect(databaseWorker.get(), & shareddatabase::DatabaseWorker::started, this, & DataObject::incrementBusy);
	connect(databaseWorker.get(), & shareddatabase::DatabaseWorker::ready, this, & DataObject::decrementBusy);
	connect(databaseWorker.get(), & shareddatabase::DatabaseWorker::striked, this, & DataObject::onDatabaseWorkerStriked);
	connect(databaseWorker.get(), & shareddatabase::DatabaseWorker::ready, databaseWorker.get(), & QObject::deleteLater);
	return databaseWorker.release();
}

void DataObject::incrementBusy()
{
	m->busy++;
	if (m->busy == 1)
		emit busyChanged();
}

void DataObject::decrementBusy()
{
	m->busy--;
	if (m->busy == 0)
		emit busyChanged();
}

void DataObject::processErrors()
{
	QMutexLocker locker(& m->sqlErrorsMutex);
	for (SQLErrorsContainer::iterator it = m->sqlErrors.begin(); it != m->sqlErrors.end(); ++it)
		if (it->isValid()) {
			emit errored(CUTEHMI_ERROR(it->text()));
		} else
			CUTEHMI_DEBUG("Query was successful.");
	m->sqlErrors.clear();
}

void DataObject::printError(InplaceError error) const
{
	CUTEHMI_CRITICAL(error.str());
}

void DataObject::onDatabaseWorkerStriked(const QString & reason)
{
	emit errored(QObject::tr("Database worker striked, because of following reason: %1.").arg(reason));
}

}
}
