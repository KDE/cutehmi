#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_EVENTTABLE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_EVENTTABLE_HPP

#include "common.hpp"
#include "TableObject.hpp"
#include "TagCache.hpp"
#include "TableNameTraits.hpp"

#include <QHash>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

template <typename T>
class  EventTable:
	public TableObject
{
	public:
		typedef T type;

		struct Tuple
		{
			T value = T();
			QDateTime time;
		};

		EventTable(TagCache * tagCache, Schema * schema, QObject * parent = nullptr);

		void insert(const QString & tagName, const Tuple & tuple);

	protected:
		TagCache * tagCache() const;

	private:
		struct Members
		{
			TagCache * tagCache;
		};

		MPtr<Members> m;
};

template <typename T>
EventTable<T>::EventTable(TagCache * tag, Schema * schema, QObject * parent):
	TableObject(schema, parent),
	m(new Members{tag})
{
}

template <typename T>
void EventTable<T>::insert(const QString & tagName, const EventTable<T>::Tuple & tuple)
{
	QString tableName = TableNameTraits<T>::Affixed("event");

	worker([this, tagName, tuple, tableName](QSqlDatabase & db) {
		if (db.driverName() == "QPSQL") {
			QSqlQuery query(db);
			CUTEHMI_DEBUG("Storing '" << tableName << "' values...");

			query.prepare(QString("INSERT INTO %1.%2(tag_id, value, time) VALUES (:tagId, :value, :time)").arg(schema()->name()).arg(tableName));
			query.bindValue(":tagId", tagCache()->getId(tagName, db));
			query.bindValue(":value", tuple.value);
			query.bindValue(":time", tuple.time);
			query.exec();

			pushError(query.lastError());
			query.finish();
		} else if (db.driverName() == "QSQLITE") {
			QSqlQuery query(db);
			CUTEHMI_DEBUG("Storing '" << tableName << "' values...");

			query.prepare(QString("INSERT INTO [%1.%2](tag_id, value, time) VALUES (:tagId, :value, :time)").arg(schema()->name()).arg(tableName));
			query.bindValue(":tagId", tagCache()->getId(tagName, db));
			query.bindValue(":value", tuple.value);
			query.bindValue(":time", tuple.time);
			query.exec();

			pushError(query.lastError());
			query.finish();
		} else
			emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
	})->work();
}

template <typename T>
TagCache * EventTable<T>::tagCache() const
{
	return m->tagCache;
}

}
}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
