#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_RECENCYTABLE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_RECENCYTABLE_HPP

#include "common.hpp"
#include "TableObject.hpp"
#include "TagCache.hpp"
#include "TableNameTraits.hpp"

#include <QHash>

#include <limits>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

template <typename T>
class RecencyTable:
	public TableObject
{
	public:
		typedef T type;

		struct Tuple
		{
			T value = T();
			QDateTime time;
		};

		typedef QHash<QString, Tuple> TuplesContainer;

		RecencyTable(TagCache * tagCache, Schema * schema, QObject * parent = nullptr);

		void update(const TuplesContainer & tuples);

	protected:
		struct ColumnValues
		{
			QStringList tagName;
			QVariantList value;
			QVariantList time;

			ColumnValues(const TuplesContainer & tuples);
		};

		TagCache * tagCache() const;

	private:
		struct Members
		{
			TagCache * tagCache;
		};

		MPtr<Members> m;
};

template <typename T>
RecencyTable<T>::RecencyTable(TagCache * tag, Schema * schema, QObject * parent):
	TableObject(schema, parent),
	m(new Members{tag})
{
}

template <typename T>
void RecencyTable<T>::update(const RecencyTable<T>::TuplesContainer & tuples)
{
	ColumnValues columnValues(tuples);
	QString tableName = TableNameTraits<T>::Affixed("recency");

	worker([this, columnValues, tableName](QSqlDatabase & db) {
		if (db.driverName() == "QPSQL") {
			QSqlQuery query(db);
			CUTEHMI_DEBUG("Storing '" << tableName << "' values...");
			QVariantList tagIds;
			for (QStringList::const_iterator tagName = columnValues.tagName.begin(); tagName != columnValues.tagName.end(); ++tagName)
				tagIds.append(tagCache()->getId(*tagName, db));

			query.prepare(QString("INSERT INTO %1.%2 (tag_id, value, time) VALUES (:tagId, :value, :time)"
							" ON CONFLICT (tag_id) DO UPDATE SET(value, time) = (:value, :time) WHERE %1.%2.tag_id = :tagId").arg(schema()->name()).arg(tableName));
			query.bindValue(":tagId", tagIds);
			query.bindValue(":value", columnValues.value);
			query.bindValue(":time", columnValues.time);
			query.execBatch();

			pushError(query.lastError());
			query.finish();
		} else if (db.driverName() == "QSQLITE") {
			QSqlQuery query(db);
			CUTEHMI_DEBUG("Storing '" << tableName << "' values...");
			QVariantList tagIds;
			for (QStringList::const_iterator tagName = columnValues.tagName.begin(); tagName != columnValues.tagName.end(); ++tagName)
				tagIds.append(tagCache()->getId(*tagName, db));

			query.prepare(QString("INSERT INTO [%1.%2] (tag_id, value, time) VALUES (:tagId, :value, :time)"
							" ON CONFLICT (tag_id) DO UPDATE SET(value, time) = (:value, :time)").arg(schema()->name()).arg(tableName));
			query.bindValue(":tagId", tagIds);
			query.bindValue(":value", columnValues.value);
			query.bindValue(":time", columnValues.time);
			query.execBatch();

			pushError(query.lastError());
			query.finish();
		} else
			emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
	})->work();
}

template <typename T>
RecencyTable<T>::ColumnValues::ColumnValues(const RecencyTable<T>::TuplesContainer & tuples)
{
	for (typename RecencyTable<T>::TuplesContainer::const_iterator it = tuples.begin(); it != tuples.end(); ++it) {
		tagName.append(it.key());
		value.append(it->value);
		time.append(it->time);
	}
}

template <typename T>
TagCache * RecencyTable<T>::tagCache() const
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
