#ifndef EVENTTABLE_HPP
#define EVENTTABLE_HPP

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

#endif // INTHISTORY_HPP
