#include <cutehmi/shareddatabase/DataObject.hpp>

#include <QMutexLocker>

namespace cutehmi {
namespace shareddatabase {

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

DatabaseWorker * DataObject::worker(std::function<void (QSqlDatabase & db)> task) const
{
	std::unique_ptr<DatabaseWorker> databaseWorker(new DatabaseWorker(m->connectionName, task));
	connect(databaseWorker.get(), & DatabaseWorker::ready, this, & DataObject::processErrors);
	connect(databaseWorker.get(), & DatabaseWorker::started, this, & DataObject::incrementBusy);
	connect(databaseWorker.get(), & DatabaseWorker::ready, this, & DataObject::decrementBusy);
	connect(databaseWorker.get(), & DatabaseWorker::striked, this, & DataObject::onDatabaseWorkerStriked);
	connect(databaseWorker.get(), & DatabaseWorker::ready, databaseWorker.get(), & QObject::deleteLater);
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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
