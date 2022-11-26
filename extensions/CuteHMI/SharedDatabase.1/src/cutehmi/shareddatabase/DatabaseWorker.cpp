#include <cutehmi/shareddatabase/DatabaseWorker.hpp>

#include "internal/DatabaseDictionary.hpp"

#include <QSqlDatabase>
#include <QSqlDriver>

namespace cutehmi {
namespace shareddatabase {

DatabaseWorker::DatabaseWorker(const QString & connectionName, std::function<void (QSqlDatabase & db)> task):
	m(new Members{connectionName, task, nullptr, {}})
{
	connect(& internal::DatabaseDictionary::Instance(), & internal::DatabaseDictionary::threadChanged, this, & DatabaseWorker::updateDbThread);
	instantiateWorker();
}

void DatabaseWorker::setTask(std::function<void (QSqlDatabase & db)> task)
{
	m->task = task;
}

void DatabaseWorker::job(QSqlDatabase & db)
{
	if (m->task)
		m->task(db);
}

void DatabaseWorker::wait() const
{
	m->worker->wait();
}

bool DatabaseWorker::isReady() const
{
	return m->worker->isReady();
}

bool DatabaseWorker::isWorking() const
{
	return m->worker->isWorking();
}

void DatabaseWorker::work()
{
	emit started();
	m->worker->work();
}


QThread * DatabaseWorker::dbThread() const
{
	return internal::DatabaseDictionary::Instance().associatedThread(m->connectionName);
}

QSqlDatabase * DatabaseWorker::db()
{
	return m->db.get();
}

const QSqlDatabase * DatabaseWorker::db() const
{
	return m->db.get();
}

void DatabaseWorker::updateDbThread(const QString & connectionName)
{
	if (connectionName == m->connectionName) {
		if (m->worker)
			m->worker->wait();
		instantiateWorker();
	}
}

void DatabaseWorker::instantiateWorker()
{
	m->worker.reset(new Worker([this]() {
		m->db.reset(new QSqlDatabase(QSqlDatabase::database(m->connectionName)));
		if (!m->db->isOpen()) {
			CUTEHMI_CRITICAL("Database worker '" << this << "' refuses to do the job, because database connection '" << m->connectionName << "' is not open.");
			emit refused(QObject::tr("database connection '%1' is not open").arg(m->connectionName));
		} else
			job(*m->db);
		m->db.reset();
	}));
	if (dbThread()) {
		if (dbThread() == QThread::currentThread())
			CUTEHMI_DEBUG("Database worker for connection '" << m->connectionName << "' will operate from current thread.");
		else {
			m->worker->employ(*dbThread(), false);
			CUTEHMI_DEBUG("Database worker for connection '" << m->connectionName << "' has been employed in dedicated database thread.");
		}
	} else
		CUTEHMI_WARNING("Database worker for connection '" << m->connectionName << "' will operate from current thread, because upon its creation there was no dedicated database thread associated with that connection in shared database dictionary.");
	connect(m->worker.get(), & Worker::ready, this, & DatabaseWorker::ready);
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
