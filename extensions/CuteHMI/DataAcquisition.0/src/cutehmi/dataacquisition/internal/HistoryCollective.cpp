#include <cutehmi/dataacquisition/internal/HistoryCollective.hpp>
#include <cutehmi/dataacquisition/internal/TableNameTraits.hpp>

#include "helpers.hpp"

namespace cutehmi {
namespace dataacquisition {
namespace internal {

const char * HistoryCollective::TABLE_STEM = "history";

HistoryCollective::HistoryCollective()
{
}

void HistoryCollective::insert(const TuplesContainer & tuples)
{
	ColumnValues intValues;
	ColumnValues boolValues;
	ColumnValues realValues;
	ToColumnValues(intValues, boolValues, realValues, tuples);
	QString schemaName = getSchemaName();

	worker([this, intValues, boolValues, realValues, schemaName](QSqlDatabase & db) {
		tableInsert<int>(db, schemaName, intValues);
		tableInsert<bool>(db, schemaName, boolValues);
		tableInsert<double>(db, schemaName, realValues);
	})->work();
}

void HistoryCollective::select(const QStringList & tags, const QDateTime & from, const QDateTime & to)
{
	QString schemaName = getSchemaName();

	worker([this, schemaName, tags, from, to](QSqlDatabase & db) {
		// Find min open time.
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
		QDateTime minOpenTime = QDateTime::fromMSecsSinceEpoch(0, Qt::UTC).addYears(static_cast<qint32>(QDateTime::YearRange::Last) - 1970);
#else
		QDateTime minOpenTime = QDateTime::fromMSecsSinceEpoch(0, Qt::UTC).addYears(292278994 - 1970);
#endif
		if (!tableMinOpenTime<bool>(db, minOpenTime, schemaName)
				|| !tableMinOpenTime<int>(db, minOpenTime, schemaName)
				|| !tableMinOpenTime<double>(db, minOpenTime, schemaName))
			return;

		// Find max close time.
		QDateTime maxCloseTime = QDateTime::fromMSecsSinceEpoch(0, Qt::UTC);
		if (!tableMaxCloseTime<bool>(db, maxCloseTime, schemaName)
				|| !tableMaxCloseTime<int>(db, maxCloseTime, schemaName)
				|| !tableMaxCloseTime<double>(db, maxCloseTime, schemaName))
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
			// Individual tables are sorted by close time in descending order by database engine, but we need to merge them into single result.
			ColumnValues mergedValues;
			mergeColumnValues<ColumnValues, SIZE>(mergedValues, columnValues, [](const ColumnValues & a, int aIndex, const ColumnValues & b, int bIndex) -> bool {
				return a.closeTime.at(aIndex).toDateTime() < b.closeTime.at(bIndex).toDateTime();
			});

			emit selected(std::move(mergedValues), minOpenTime, maxCloseTime);
		} else
			return;
	})->work();
}

QVariant::Type HistoryCollective::TupleVariantType(const HistoryCollective::Tuple & tuple)
{
	QVariant::Type result = tuple.open.type();

	CUTEHMI_ASSERT(tuple.close.type() == result && tuple.max.type() == result && tuple.min.type() == result, "Inconsistent data types in tuple.");

	return result;
}

void HistoryCollective::ToColumnValues(ColumnValues & intValues, ColumnValues & boolValues, ColumnValues & realValues, const TuplesContainer & tuples)
{
	for (TuplesContainer::const_iterator it = tuples.begin(); it != tuples.end(); ++it) {
		ColumnValues * values;
		switch (TupleVariantType(*it)) {
			case QVariant::Int:
				values = & intValues;
				break;
			case QVariant::Bool:
				values = & boolValues;
				break;
			case QVariant::Double:
				values = & realValues;
				break;
			default:
				CUTEHMI_CRITICAL("Unsupported data type ('" << it->open.typeName() << "') provided for 'value' field.");
				continue;	// Continue to next iteration.
		}
		values->tagName.append(it.key());
		values->open.append(it->open);
		values->close.append(it->close);
		values->min.append(it->min);
		values->max.append(it->max);
		values->openTime.append(it->openTime);
		values->closeTime.append(it->closeTime);
		values->count.append(it->count);
	}
}

QString HistoryCollective::insertQuery(const QString & driverName, const QString & schemaName, const QString & tableName)
{
	if (driverName == "QPSQL")
		return QString("INSERT INTO %1.%2(tag_id, open, close, min, max, open_time, close_time, count) VALUES (:tagId, :open, :close, :min, :max, :open_time, :close_time, :count)").arg(schemaName, tableName);
	else if (driverName == "QSQLITE")
		return QString("INSERT INTO [%1.%2](tag_id, open, close, min, max, open_time, close_time, count) VALUES (:tagId, :open, :close, :min, :max, :open_time, :close_time, :count)").arg(schemaName, tableName);
	else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(driverName)));
	return QString();
}

QString HistoryCollective::selectQuery(const QString & driverName, const QString & schemaName, const QString & tableName, const QStringList & tagIdtrings, const QDateTime & from, const QDateTime & to)
{
	if (driverName == "QPSQL") {
		QStringList whereClauses;
		if (from.isValid())
			whereClauses.append("open_time >= :from");
		if (to.isValid())
			whereClauses.append("close_time <= :to");
		if (!tagIdtrings.isEmpty())
			whereClauses.append(QString("%1.%2.tag_id IN (%3)").arg(schemaName, tableName, tagIdtrings.join(',')));
		QString where;
		if (!whereClauses.isEmpty())
			where = QString(" WHERE ") + whereClauses.join(" AND ");
		return QString("SELECT * FROM %1.%2 LEFT JOIN %1.tag ON %1.%2.tag_id = %1.tag.id").arg(schemaName, tableName).append(where).append(" ORDER BY close_time DESC");
	} else if (driverName == "QSQLITE") {
		QStringList whereClauses;
		if (from.isValid())
			whereClauses.append("open_time >= :from");
		if (to.isValid())
			whereClauses.append("close_time <= :to");
		if (!tagIdtrings.isEmpty())
			whereClauses.append(QString("[%1.%2].tag_id IN (%3)").arg(schemaName, tableName, tagIdtrings.join(',')));
		QString where;
		if (!whereClauses.isEmpty())
			where = QString(" WHERE ") + whereClauses.join(" AND ");
		return QString("SELECT * FROM [%1.%2] LEFT JOIN [%1.tag] ON [%1.%2].tag_id = [%1.tag].id").arg(schemaName, tableName).append(where).append(" ORDER BY close_time DESC");
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(driverName)));
	return QString();
}

template<typename T>
void HistoryCollective::tableInsert(QSqlDatabase & db, const QString & schemaName, const ColumnValues & columnValues)
{
	QString tableName = TableNameTraits<T>::Affixed(TABLE_STEM);

	QSqlQuery query(db);
	query.setForwardOnly(true);
	CUTEHMI_DEBUG("Storing '" << tableName << "' values...");
	QVariantList tagIds;
	for (QStringList::const_iterator tagName = columnValues.tagName.begin(); tagName != columnValues.tagName.end(); ++tagName)
		tagIds.append(tagCache()->getId(*tagName, db));

	query.prepare(insertQuery(db.driverName(), schemaName, tableName));
	query.bindValue(":tagId", tagIds);
	query.bindValue(":open", columnValues.open);
	query.bindValue(":close", columnValues.close);
	query.bindValue(":min", columnValues.min);
	query.bindValue(":max", columnValues.max);
	query.bindValue(":open_time", columnValues.openTime);
	query.bindValue(":close_time", columnValues.closeTime);
	query.bindValue(":count", columnValues.count);
	query.execBatch();

	pushError(query.lastError(), query.lastQuery());
	query.finish();
}

template<typename T>
bool HistoryCollective::tableSelect(QSqlDatabase & db, ColumnValues & columnValues, const QString & schemaName, const QStringList & tags, const QDateTime & from, const QDateTime & to)
{
	QString tableName = TableNameTraits<T>::Affixed(TABLE_STEM);

	QStringList tagIdStrings;
	if (!tags.isEmpty()) {
		for (auto && tag : tags)
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
		int openIndex = query.record().indexOf("open");
		int closeIndex = query.record().indexOf("close");
		int minIndex = query.record().indexOf("min");
		int maxIndex = query.record().indexOf("max");
		int openTimeIndex = query.record().indexOf("open_time");
		int closeTimeIndex = query.record().indexOf("close_time");
		int countIndex = query.record().indexOf("count");
		while (query.next()) {
			columnValues.tagName.append(query.value(nameIndex).toString());
			columnValues.open.append(query.value(openIndex).value<T>());
			columnValues.close.append(query.value(closeIndex).value<T>());
			columnValues.min.append(query.value(minIndex).value<T>());
			columnValues.max.append(query.value(maxIndex).value<T>());
			columnValues.openTime.append(query.value(openTimeIndex).toDateTime());
			columnValues.closeTime.append(query.value(closeTimeIndex).toDateTime());
			columnValues.count.append(query.value(countIndex).toInt());
		}

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	}

	return false;
}

template<typename T>
bool HistoryCollective::tableMinOpenTime(QSqlDatabase & db, QDateTime & minOpenTime, const QString & schemaName)
{
	QString tableName = TableNameTraits<T>::Affixed(TABLE_STEM);

	if (db.driverName() == "QPSQL") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Looking for open time minimum...");

		query.prepare(QString("SELECT MIN(open_time) FROM %1.%2").arg(schemaName, tableName));
		query.exec();

		if (query.next())
			minOpenTime = std::min(minOpenTime, query.value(0).toDateTime());

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	} else if (db.driverName() == "QSQLITE") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Looking for open time minimum...");

		query.prepare(QString("SELECT MIN(open_time) FROM [%1.%2]").arg(schemaName, tableName));
		query.exec();

		if (query.next())
			minOpenTime = std::min(minOpenTime, query.value(0).toDateTime());

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));

	return false;
}

template<typename T>
bool HistoryCollective::tableMaxCloseTime(QSqlDatabase & db, QDateTime & maxCloseTime, const QString & schemaName)
{
	QString tableName = TableNameTraits<T>::Affixed(TABLE_STEM);

	if (db.driverName() == "QPSQL") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Looking for close time maximum...");

		query.prepare(QString("SELECT MAX(close_time) FROM %1.%2").arg(schemaName, tableName));
		query.exec();

		if (query.next())
			maxCloseTime = std::max(maxCloseTime, query.value(0).toDateTime());

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	} else if (db.driverName() == "QSQLITE") {
		QSqlQuery query(db);
		query.setForwardOnly(true);
		CUTEHMI_DEBUG("Looking for close time maximum...");

		query.prepare(QString("SELECT MAX(close_time) FROM [%1.%2]").arg(schemaName, tableName));
		query.exec();

		if (query.next())
			maxCloseTime = std::max(maxCloseTime, query.value(0).toDateTime());

		pushError(query.lastError(), query.lastQuery());

		if (!query.lastError().isValid())
			return true;
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(db.driverName())));

	return false;
}

//<CuteHMI.DataAcquisition-1.workaround target="clang" cause="Bug-28280">
HistoryCollective::ColumnValues::~ColumnValues()
{
}
//</CuteHMI.DataAcquisition-1.workaround>

int HistoryCollective::ColumnValues::length() const
{
	CUTEHMI_ASSERT(tagName.count() == open.count(), "inconsistency in element count, which should be the same for each column");
	CUTEHMI_ASSERT(tagName.count() == close.count(), "inconsistency in element count, which should be the same for each column");
	CUTEHMI_ASSERT(tagName.count() == min.count(), "inconsistency in element count, which should be the same for each column");
	CUTEHMI_ASSERT(tagName.count() == max.count(), "inconsistency in element count, which should be the same for each column");
	CUTEHMI_ASSERT(tagName.count() == openTime.count(), "inconsistency in element count, which should be the same for each column");
	CUTEHMI_ASSERT(tagName.count() == closeTime.count(), "inconsistency in element count, which should be the same for each column");
	CUTEHMI_ASSERT(tagName.count() == count.count(), "inconsistency in element count, which should be the same for each column");

	return tagName.count();
}

bool HistoryCollective::ColumnValues::isEqual(int i, const HistoryCollective::ColumnValues & other)
{
	return open.at(i) == other.open.at(i)
			&& close.at(i) == other.close.at(i)
			&& min.at(i) == other.min.at(i)
			&& max.at(i) == other.max.at(i)
			&& openTime.at(i) == other.openTime.at(i)
			&& closeTime.at(i) == other.closeTime.at(i)
			&& count.at(i) == other.count.at(i)
			&& tagName.at(i) == other.tagName.at(i);
}

void HistoryCollective::ColumnValues::replace(int i, const HistoryCollective::ColumnValues & other)
{
	tagName.replace(i, other.tagName.at(i));
	open.replace(i, other.open.at(i));
	close.replace(i, other.close.at(i));
	min.replace(i, other.min.at(i));
	max.replace(i, other.max.at(i));
	openTime.replace(i, other.openTime.at(i));
	closeTime.replace(i, other.closeTime.at(i));
	count.replace(i, other.count.at(i));
}

void HistoryCollective::ColumnValues::insert(int i, const HistoryCollective::ColumnValues & other)
{
	tagName.insert(i, other.tagName.at(i));
	open.insert(i, other.open.at(i));
	close.insert(i, other.close.at(i));
	min.insert(i, other.min.at(i));
	max.insert(i, other.max.at(i));
	openTime.insert(i, other.openTime.at(i));
	closeTime.insert(i, other.closeTime.at(i));
	count.insert(i, other.count.at(i));
}

void HistoryCollective::ColumnValues::eraseFrom(int i)
{
	tagName.erase(tagName.begin() + i, tagName.end());
	open.erase(open.begin() + i, open.end());
	close.erase(close.begin() + i, close.end());
	min.erase(min.begin() + i, min.end());
	max.erase(max.begin() + i, max.end());
	openTime.erase(openTime.begin() + i, openTime.end());
	closeTime.erase(closeTime.begin() + i, closeTime.end());
	count.erase(count.begin() + i, count.end());
}

void HistoryCollective::ColumnValues::append(const HistoryCollective::ColumnValues & other, int i)
{
	tagName.append(other.tagName.at(i));
	open.append(other.open.at(i));
	close.append(other.close.at(i));
	min.append(other.min.at(i));
	max.append(other.max.at(i));
	openTime.append(other.openTime.at(i));
	closeTime.append(other.closeTime.at(i));
	count.append(other.count.at(i));
}

}
}
}

//(c)C: Copyright © 2020-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
