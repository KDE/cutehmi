#ifndef RECENCYTABLE_HPP
#define RECENCYTABLE_HPP

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
