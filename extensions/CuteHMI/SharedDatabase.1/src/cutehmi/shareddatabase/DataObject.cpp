#include "DataObject.hpp"

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

void DataObject::pushError(const QSqlError & sqlError, const QString & query)
{
	QMutexLocker locker(& m->sqlErrorsMutex);
	m->sqlErrors.append({sqlError, query});
}

DatabaseWorker * DataObject::worker(std::function<void (QSqlDatabase & db)> task) const
{
	std::unique_ptr<DatabaseWorker> databaseWorker(new DatabaseWorker(m->connectionName, task));
	connect(databaseWorker.get(), & DatabaseWorker::ready, this, & DataObject::processErrors);
	connect(databaseWorker.get(), & DatabaseWorker::started, this, & DataObject::incrementBusy);
	connect(databaseWorker.get(), & DatabaseWorker::ready, this, & DataObject::decrementBusy);
	connect(databaseWorker.get(), & DatabaseWorker::refused, this, & DataObject::onDatabaseWorkerRefused);
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
		if (it->first.isValid()) {
			CUTEHMI_DEBUG("Query '" << it->second << "' has failed.");
			emit errored(CUTEHMI_ERROR(it->first.text()));
		} else
			CUTEHMI_DEBUG("Query '" << it->second << "' was successful.");
	m->sqlErrors.clear();
}

void DataObject::printError(InplaceError error) const
{
	CUTEHMI_CRITICAL(error.str());
}

void DataObject::onDatabaseWorkerRefused(const QString & reason)
{
	emit errored(QObject::tr("Database worker has refused to do the job, because of following reason: %1.").arg(reason));
}

}
}

//(c)C: Copyright © 2022-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
