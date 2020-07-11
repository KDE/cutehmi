#include <cutehmi/dataacquisition/internal/EventCollective.hpp>
#include <cutehmi/dataacquisition/internal/TableNameTraits.hpp>
#include <cutehmi/dataacquisition/TagValue.hpp>

#include "helpers.hpp"

namespace cutehmi {
namespace dataacquisition {
namespace internal {

const char * EventCollective::TABLE_STEM = "event";

EventCollective::EventCollective()
{
}

void EventCollective::insert(const TagValue & tag)
{
	switch (tag.value().type()) {
		case QVariant::Int:
			insertIntoTable<int>(tag);
			break;
		case QVariant::Bool:
			insertIntoTable<bool>(tag);
			break;
		case QVariant::Double:
			insertIntoTable<double>(tag);
			break;
		default:
			CUTEHMI_CRITICAL("Unsupported type ('" << tag.value().typeName() << "') provided as a 'value' of 'TagValue' object.");
	}
}

void EventCollective::select(const QStringList & tags, const QDateTime & from, const QDateTime & to)
{
	QString schemaName = getSchemaName();

	worker([this, schemaName, tags, from, to](QSqlDatabase & db) {
		// Find min time.
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
		QDateTime minTime = QDateTime::fromMSecsSinceEpoch(0, Qt::UTC).addYears(static_cast<qint32>(QDateTime::YearRange::Last) - 1970);
#else
		QDateTime minTime = QDateTime::fromMSecsSinceEpoch(0, Qt::UTC).addYears(292278994 - 1970);
#endif
		if (!tableMinTime<bool>(db, minTime, schemaName)
				|| !tableMinTime<int>(db, minTime, schemaName)
				|| !tableMinTime<double>(db, minTime, schemaName))
			return;

		// Find max time.
		QDateTime maxTime = QDateTime::fromMSecsSinceEpoch(0, Qt::UTC);
		if (!tableMaxTime<bool>(db, maxTime, schemaName)
				|| !tableMaxTime<int>(db, maxTime, schemaName)
				|| !tableMaxTime<double>(db, maxTime, schemaName))
			return;

		// Actual results.
		constexpr int BOOL = 0;
		constexpr int INT = 1;
		constexpr int DOUBLE = 2;
		constexpr int SIZE = 3;
		ColumnValues columnValues[SIZE];
		if (tableSelect<bool>(db, columnValues[BOOL], schemaName, tags, from, to)
				&& tableSelect<int>(db, columnValues[INT], schemaName, tags, from, to)
				&& tableSelect<double>(db, columnValues[DOUBLE], schemaName, tags, from, to)) {

			// Individual tables are sorted by time in descending order by database engine, but we need to merge them into single result.

			ColumnValues mergedValues;
			mergeColumnValues<ColumnValues, SIZE>(mergedValues, columnValues, [](const ColumnValues & a, int aIndex, const ColumnValues & b, int bIndex) -> bool {
				return a.time.at(aIndex).toDateTime() < b.time.at(bIndex).toDateTime();
			});

			emit selected(std::move(mergedValues), minTime, maxTime);
		} else
			return;
	})->work();
}

QString EventCollective::selectQuery(const QString & driverName, const QString & schemaName, const QString & tableName, const QStringList & tagIdtrings, const QDateTime & from, const QDateTime & to)
{
	if (driverName == "QPSQL") {
		QStringList whereClauses;
		if (from.isValid())
			whereClauses.append("time >= :from");
		if (to.isValid())
			whereClauses.append("time <= :to");
		if (!tagIdtrings.isEmpty())
			whereClauses.append(QString("%1.%2.tag_id IN (%3)").arg(schemaName).arg(tableName).arg(tagIdtrings.join(',')));
		QString where;
		if (!whereClauses.isEmpty())
			where = QString(" WHERE ") + whereClauses.join(" AND ");
		return QString("SELECT * FROM %1.%2 LEFT JOIN %1.tag ON %1.%2.tag_id = %1.tag.id").arg(schemaName).arg(tableName).append(where).append(" ORDER BY time DESC");
	} else if (driverName == "QSQLITE") {
		QStringList whereClauses;
		if (from.isValid())
			whereClauses.append("time >= :from");
		if (to.isValid())
			whereClauses.append("time <= :to");
		if (!tagIdtrings.isEmpty())
			whereClauses.append(QString("[%1.%2].tag_id IN (%3)").arg(schemaName).arg(tableName).arg(tagIdtrings.join(',')));
		QString where;
		if (!whereClauses.isEmpty())
			where = QString(" WHERE ") + whereClauses.join(" AND ");
		return QString("SELECT * FROM [%1.%2] LEFT JOIN [%1.tag] ON [%1.%2].tag_id = [%1.tag].id").arg(schemaName).arg(tableName).append(where).append(" ORDER BY time DESC");
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(driverName)));
	return QString();
}

template<typename T>
bool EventCollective::tableSelect(QSqlDatabase & db, ColumnValues & columnValues, const QString & schemaName, const QStringList & tags, const QDateTime & from, const QDateTime & to)
{
	QString tableName = TableNameTraits<T>::Affixed(TABLE_STEM);

	QStringList tagIdStrings;
	if (!tags.isEmpty()) {
		for (auto tag : tags)
			tagIdStrings.append(QString::number(tagCache()->getId(tag, db)));
	}

	QSqlQuery query(db);
	query.setForwardOnly(true);
	CUTEHMI_DEBUG("Reading '" << tableName << "' values...");

	QString queryString = selectQuery(db.driverName(), schemaName, tableName, tagIdStrings, from, to);
	if (!queryString.isNull()) {
		query.prepare(queryString);
		query.bindValue(":from", from);
		query.bindValue(":to", to);
		query.exec();

		int nameIndex = query.record().indexOf("name");
		int valueIndex = query.record().indexOf("value");
		int timeIndex = query.record().indexOf("time");
		while (query.next()) {
			columnValues.tagName.append(query.value(nameIndex).toString());
			columnValues.value.append(query.value(valueIndex).value<T>());
			columnValues.time.append(query.value(timeIndex).toDateTime());
		}

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	}

	return false;
}

template<typename T>
bool EventCollective::tableMinTime(QSqlDatabase & db, QDateTime & minTime, const QString & schemaName)
{
	QString tableName = TableNameTraits<T>::Affixed(TABLE_STEM);

	if (db.driverName() == "QPSQL") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Looking for time minimum...");

		query.prepare(QString("SELECT MIN(time) FROM %1.%2").arg(schemaName).arg(tableName));
		query.exec();

		if (query.next())
			minTime = std::min(minTime, query.value(0).toDateTime());

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	} else if (db.driverName() == "QSQLITE") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Looking for time minimum...");

		query.prepare(QString("SELECT MIN(time) FROM [%1.%2]").arg(schemaName).arg(tableName));
		query.exec();

		if (query.next())
			minTime = std::min(minTime, query.value(0).toDateTime());

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));

	return false;
}

template<typename T>
bool EventCollective::tableMaxTime(QSqlDatabase & db, QDateTime & maxTime, const QString & schemaName)
{
	QString tableName = TableNameTraits<T>::Affixed(TABLE_STEM);

	if (db.driverName() == "QPSQL") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Looking for time maximum...");

		query.prepare(QString("SELECT MAX(time) FROM %1.%2").arg(schemaName).arg(tableName));
		query.exec();

		if (query.next())
			maxTime = std::max(maxTime, query.value(0).toDateTime());

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	} else if (db.driverName() == "QSQLITE") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Looking for time maximum...");

		query.prepare(QString("SELECT MAX(time) FROM [%1.%2]").arg(schemaName).arg(tableName));
		query.exec();

		if (query.next())
			maxTime = std::max(maxTime, query.value(0).toDateTime());

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));

	return false;
}

template<typename T>
void EventCollective::insertIntoTable(const TagValue & tag)
{
	QString schemaName = getSchemaName();
	QString tagName = tag.name();
	Tuple tuple = {tag.value(), QDateTime::currentDateTimeUtc()};

	worker([this, schemaName, tagName, tuple](QSqlDatabase & db) {
		QString tableName = TableNameTraits<T>::Affixed(TABLE_STEM);

		QString queryString;
		if (db.driverName() == "QPSQL")
			queryString = "INSERT INTO %1.%2(tag_id, value, time) VALUES (:tagId, :value, :time)";
		else if (db.driverName() == "QSQLITE")
			queryString = "INSERT INTO [%1.%2](tag_id, value, time) VALUES (:tagId, :value, :time)";
		else {
			emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));
			return;
		}

		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Storing '" << tableName << "' values...");

		query.prepare(queryString.arg(schemaName).arg(tableName));
		query.bindValue(":tagId", tagCache()->getId(tagName, db));
		query.bindValue(":value", tuple.value);
		query.bindValue(":time", tuple.time);
		query.exec();

		pushError(query.lastError(), query.lastQuery());
	})->work();
}

//<CuteHMI.DataAcquisition-1.workaround target="clang" cause="Bug-28280">
EventCollective::ColumnValues::~ColumnValues()
{
}
//</CuteHMI.DataAcquisition-1.workaround>

int EventCollective::ColumnValues::length() const
{
	CUTEHMI_ASSERT(tagName.count() == value.count(), "inconsistency in element count, which should be the same for each column");
	CUTEHMI_ASSERT(tagName.count() == time.count(), "inconsistency in element count, which should be the same for each column");

	return tagName.count();
}

bool EventCollective::ColumnValues::isEqual(int i, const EventCollective::ColumnValues & other)
{
	return time.at(i) == other.time.at(i)
			&& value.at(i) == other.value.at(i)
			&& tagName.at(i) == other.tagName.at(i);
}

void EventCollective::ColumnValues::replace(int i, const EventCollective::ColumnValues & other)
{
	tagName.replace(i, other.tagName.at(i));
	value.replace(i, other.value.at(i));
	time.replace(i, other.time.at(i));
}

void EventCollective::ColumnValues::insert(int i, const EventCollective::ColumnValues & other)
{
	tagName.insert(i, other.tagName.at(i));
	value.insert(i, other.value.at(i));
	time.insert(i, other.time.at(i));
}

void EventCollective::ColumnValues::eraseFrom(int i)
{
	tagName.erase(tagName.begin() + i, tagName.end());
	value.erase(value.begin() + i, value.end());
	time.erase(time.begin() + i, time.end());
}

void EventCollective::ColumnValues::append(const EventCollective::ColumnValues & other, int i)
{
	tagName.append(other.tagName.at(i));
	value.append(other.value.at(i));
	time.append(other.time.at(i));
}

}
}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
