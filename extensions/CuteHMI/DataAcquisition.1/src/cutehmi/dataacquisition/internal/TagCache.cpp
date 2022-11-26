#include <cutehmi/dataacquisition/internal/TagCache.hpp>

#include <QSqlRecord>
#include <QSqlResult>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

TagCache::TagCache(Schema * schema, QObject * parent):
	TableObject(schema, parent),
	m(new Members)
{
}

int TagCache::getId(const QString & name, QSqlDatabase & db)
{
	TagIdContainter::const_iterator tag;
	TagIdContainter::const_iterator tagIdsEnd;
	bool tagIdsEmpty;

	// Access to m->tagIds is a critical section.
	{
		QReadLocker locker(& m->tagIdsLock);
		tag = m->tagIds.constFind(name);
		tagIdsEnd = m->tagIds.constEnd();
		tagIdsEmpty = m->tagIds.empty();
	}

	if (tag == tagIdsEnd) {
		// If tag ids map is empty update it from database.
		if (tagIdsEmpty) {
			update(db);
			{
				QReadLocker locker(& m->tagIdsLock);
				tag = m->tagIds.constFind(name);
				tagIdsEnd = m->tagIds.constEnd();
			}
		}

		// If tag wasn't found it probably does not exist in database, so insert it.
		if (tag == tagIdsEnd) {
			insert(name, db);
			{
				QReadLocker locker(& m->tagIdsLock);
				tag = m->tagIds.constFind(name);
				tagIdsEnd = m->tagIds.constEnd();
			}

			// If insert query fails, then some other thread might have inserted it.
			if (tag == tagIdsEnd) {
				update(db);
				{
					QReadLocker locker(& m->tagIdsLock);
					tag = m->tagIds.constFind(name);
				}
			}
		}

		processErrors();
	}

	return tag.value();
}

void TagCache::insert(const QString & name, QSqlDatabase & db)
{
	if (db.driverName() == "QPSQL") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Inserting '" << name << "' tag...");

		query.prepare(QString("INSERT INTO %1.tag (name) VALUES (:name) RETURNING id").arg(schema()->name()));
		query.bindValue(":name", name);
		query.exec();
		int idIndex = query.record().indexOf("id");

		if (query.first()) {
			QWriteLocker locker(& m->tagIdsLock);
			m->tagIds[name] = query.value(idIndex).toInt();
		}
		pushError(query.lastError(), query.lastQuery());
	} else if (db.driverName() == "QSQLITE") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Inserting '" << name << "' tag...");

		query.prepare(QString("INSERT INTO [%1.tag] (name) VALUES (:name);").arg(schema()->name()));
		query.bindValue(":name", name);
		query.exec();
		query.finish();


		query.prepare(QString("SELECT * FROM [%1.tag] WHERE name = :name").arg(schema()->name()));
		query.bindValue(":name", name);
		query.exec();
		int idIndex = query.record().indexOf("id");
		if (query.first()) {
			QWriteLocker locker(& m->tagIdsLock);
			m->tagIds[name] = query.value(idIndex).toInt();
		}
		pushError(query.lastError(), query.lastQuery());
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
}

void TagCache::update(QSqlDatabase & db)
{
	if (db.driverName() == "QPSQL") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Updating tag cache...");

		query.exec(QString("SELECT * FROM %1.tag").arg(schema()->name()));
		int idIndex = query.record().indexOf("id");
		int nameIndex = query.record().indexOf("name");
		{
			QWriteLocker locker(& m->tagIdsLock);

			m->tagIds.clear();
			while (query.next())
				m->tagIds[query.value(nameIndex).toString()] = query.value(idIndex).toInt();
		}
		pushError(query.lastError(), query.lastQuery());
	} else if (db.driverName() == "QSQLITE") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Updating tag cache...");

		query.exec(QString("SELECT * FROM [%1.tag]").arg(schema()->name()));
		int idIndex = query.record().indexOf("id");
		int nameIndex = query.record().indexOf("name");
		{
			QWriteLocker locker(& m->tagIdsLock);

			m->tagIds.clear();
			while (query.next())
				m->tagIds[query.value(nameIndex).toString()] = query.value(idIndex).toInt();
		}
		pushError(query.lastError(), query.lastQuery());
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
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
