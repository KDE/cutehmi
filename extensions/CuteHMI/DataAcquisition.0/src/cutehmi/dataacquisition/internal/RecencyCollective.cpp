#include <cutehmi/dataacquisition/internal/RecencyCollective.hpp>
#include <cutehmi/dataacquisition/internal/TableNameTraits.hpp>

#include <QSqlField>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

const char * RecencyCollective::TABLE_STEM = "recency";

RecencyCollective::RecencyCollective()
{
}

void RecencyCollective::update(const TuplesContainer & tuples)
{
	ColumnValues intValues;
	ColumnValues boolValues;
	ColumnValues realValues;
	ToColumnValues(intValues, boolValues, realValues, tuples);
	QString schemaName = getSchemaName();

	worker([this, intValues, boolValues, realValues, schemaName](QSqlDatabase & db) {
		tableUpdate<int>(db, schemaName, intValues);
		tableUpdate<bool>(db, schemaName, boolValues);
		tableUpdate<double>(db, schemaName, realValues);
	})->work();
}

void RecencyCollective::select(const QStringList & tags)
{
	QString schemaName = getSchemaName();

	worker([this, schemaName, tags](QSqlDatabase & db) {
		ColumnValues result;

		if (tableSelect<bool>(db, result, schemaName, tags)
				&& tableSelect<int>(db, result, schemaName, tags)
				&& tableSelect<double>(db, result, schemaName, tags))
			emit selected(std::move(result));
		else
			return;
	})->work();
}

void RecencyCollective::ToColumnValues(ColumnValues & intValues, ColumnValues & boolValues, ColumnValues & realValues, const TuplesContainer & tuples)
{
	for (TuplesContainer::const_iterator it = tuples.begin(); it != tuples.end(); ++it) {
		ColumnValues * values;
		switch (it->value.type()) {
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
				CUTEHMI_CRITICAL("Unsupported data type ('" << it->value.typeName() << "') provided for 'value' field.");
				continue;	// Continue to next iteration.
		}
		values->tagName.append(it.key());
		values->value.append(it->value);
		values->time.append(it->time);
	}
}

QString RecencyCollective::updateQuery(const QString & driverName, const QString & schemaName, const QString & tableName)
{
	if (driverName == "QPSQL")
		return QString("INSERT INTO %1.%2 (tag_id, value, time) VALUES (:tagId, :value, :time)"
						" ON CONFLICT (tag_id) DO UPDATE SET(value, time) = (:value, :time) WHERE %1.%2.tag_id = :tagId").arg(schemaName, tableName);
	else if (driverName == "QSQLITE")
		return QString("INSERT INTO [%1.%2] (tag_id, value, time) VALUES (:tagId, :value, :time)"
						" ON CONFLICT (tag_id) DO UPDATE SET(value, time) = (:value, :time)").arg(schemaName, tableName);
	else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(driverName)));
	return QString();
}

QString RecencyCollective::selectQuery(const QString & driverName, const QString & schemaName, const QString & tableName, const QStringList & tagIdtrings)
{
	if (driverName == "QPSQL") {
		QString where;
		if (!tagIdtrings.isEmpty())
			where = QString(" WHERE %1.%2.tag_id IN (%3)").arg(schemaName, tableName, tagIdtrings.join(','));
		return QString("SELECT * FROM %1.%2 LEFT JOIN %1.tag ON %1.%2.tag_id = %1.tag.id").arg(schemaName, tableName).append(where);
	} else if (driverName == "QSQLITE") {
		QString where;
		if (!tagIdtrings.isEmpty())
			where = QString(" WHERE [%1.%2].tag_id IN (%3)").arg(schemaName, tableName, tagIdtrings.join(','));
		return QString("SELECT * FROM [%1.%2] LEFT JOIN [%1.tag] ON [%1.%2].tag_id = [%1.tag].id").arg(schemaName, tableName).append(where);
	} else
		emit errored(CUTEHMI_ERROR(tr("Driver '%1' is not supported.").arg(driverName)));
	return QString();
}

template<typename T>
void RecencyCollective::tableUpdate(QSqlDatabase & db, const QString & schemaName, const ColumnValues & columnValues)
{
	QString tableName = TableNameTraits<T>::Affixed(TABLE_STEM);

	QSqlQuery query(db);
	query.setForwardOnly(true);
	CUTEHMI_DEBUG("Storing '" << tableName << "' values...");
	QVariantList tagIds;
	for (QStringList::const_iterator tagName = columnValues.tagName.begin(); tagName != columnValues.tagName.end(); ++tagName)
		tagIds.append(tagCache()->getId(*tagName, db));

	query.prepare(updateQuery(db.driverName(), schemaName, tableName));
	query.bindValue(":tagId", tagIds);
	query.bindValue(":value", columnValues.value);
	query.bindValue(":time", columnValues.time);
	query.execBatch();

	pushError(query.lastError(), query.lastQuery());
}

template<typename T>
bool RecencyCollective::tableSelect(QSqlDatabase & db, ColumnValues & columnValues, const QString & schemaName, const QStringList & tags)
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

	QString queryString = selectQuery(db.driverName(), schemaName, tableName, tagIdStrings);
	if (!queryString.isNull()) {
		query.prepare(queryString);
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

//<CuteHMI.DataAcquisition-1.workaround target="clang" cause="Bug-28280">
RecencyCollective::ColumnValues::~ColumnValues()
{
}
//</CuteHMI.DataAcquisition-1.workaround>

int RecencyCollective::ColumnValues::length() const
{
	CUTEHMI_ASSERT(tagName.count() == value.count(), "inconsistency in element count, which should be the same for each column");
	CUTEHMI_ASSERT(tagName.count() == time.count(), "inconsistency in element count, which should be the same for each column");

	return tagName.count();
}

bool RecencyCollective::ColumnValues::isEqual(int i, const RecencyCollective::ColumnValues & other)
{
	return time.at(i) == other.time.at(i)
			&& value.at(i) == other.value.at(i)
			&& tagName.at(i) == other.tagName.at(i);
}

void RecencyCollective::ColumnValues::replace(int i, const RecencyCollective::ColumnValues & other)
{
	tagName.replace(i, other.tagName.at(i));
	value.replace(i, other.value.at(i));
	time.replace(i, other.time.at(i));
}

void RecencyCollective::ColumnValues::insert(int i, const RecencyCollective::ColumnValues & other)
{
	tagName.insert(i, other.tagName.at(i));
	value.insert(i, other.value.at(i));
	time.insert(i, other.time.at(i));
}

void RecencyCollective::ColumnValues::eraseFrom(int i)
{
	tagName.erase(tagName.begin() + i, tagName.end());
	value.erase(value.begin() + i, value.end());
	time.erase(time.begin() + i, time.end());
}

void RecencyCollective::ColumnValues::append(const RecencyCollective::ColumnValues & other, int i)
{
	tagName.append(other.tagName.at(i));
	value.append(other.value.at(i));
	time.append(other.time.at(i));
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
