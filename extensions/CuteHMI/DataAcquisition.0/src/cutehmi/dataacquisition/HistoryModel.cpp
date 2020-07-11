#include <cutehmi/dataacquisition/HistoryModel.hpp>

namespace cutehmi {
namespace dataacquisition {

HistoryModel::HistoryModel(QObject * parent):
	AbstractListModel(parent),
	m(new Members{
	{},
	{},
	{},
	{},
	{},
	{},
	{}})
{
	connect(this, & HistoryModel::schemaChanged, this, & HistoryModel::onSchemaChanged);
	connect(& m->dbCollective, & internal::HistoryCollective::selected, this, & HistoryModel::onSelected);
	connect(& m->dbCollective, & internal::HistoryCollective::busyChanged, this, & HistoryModel::confirmUpdateFinished);
	connect(& m->dbCollective, & internal::HistoryCollective::errored, this, & HistoryModel::broke);
	connect(& m->dbCollective, & internal::HistoryCollective::busyChanged, this, & HistoryModel::busyChanged);
}

QStringList HistoryModel::tags() const
{
	return m->tags;
}

void HistoryModel::setTags(const QStringList & tags)
{
	if (m->tags != tags) {
		m->tags = tags;
		emit tagsChanged();
	}
}

QDateTime HistoryModel::begin() const
{
	return m->begin;
}

QDateTime HistoryModel::end() const
{
	return m->end;
}

QDateTime HistoryModel::from() const
{
	return m->from;
}

void HistoryModel::setFrom(const QDateTime & from)
{
	if (m->from != from) {
		m->from = from;
		emit fromChanged();
	}
}

QDateTime HistoryModel::to() const
{
	return m->to;
}

void HistoryModel::setTo(const QDateTime & to)
{
	if (m->to != to) {
		m->to = to;
		emit toChanged();
	}
}

bool HistoryModel::busy() const
{
	return m->dbCollective.busy();
}

QVariant HistoryModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == TAG_ROLE)
		return m->columnValues.tagName.at(index.row());

	if (role == OPEN_ROLE)
		return m->columnValues.open.at(index.row());

	if (role == CLOSE_ROLE)
		return m->columnValues.close.at(index.row());

	if (role == MIN_ROLE)
		return m->columnValues.min.at(index.row());

	if (role == MAX_ROLE)
		return m->columnValues.max.at(index.row());

	if (role == OPEN_TIME_ROLE)
		return m->columnValues.openTime.at(index.row());

	if (role == CLOSE_TIME_ROLE)
		return m->columnValues.closeTime.at(index.row());

	if (role == COUNT_ROLE)
		return m->columnValues.count.at(index.row());

	return QVariant();
}

QHash<int, QByteArray> HistoryModel::roleNames() const
{
	QHash<int, QByteArray> result = Parent::roleNames();
	result[TAG_ROLE] = "tag";
	result[OPEN_ROLE] = "open";
	result[CLOSE_ROLE] = "close";
	result[MIN_ROLE] = "min";
	result[MAX_ROLE] = "max";
	result[OPEN_TIME_ROLE] = "openTime";
	result[CLOSE_TIME_ROLE] = "closeTime";
	result[COUNT_ROLE] = "count";
	return result;
}

int HistoryModel::rowCount(const QModelIndex & parent) const
{
	if (parent.isValid())
		return 0;

	return m->columnValues.length();
}

void HistoryModel::requestUpdate()
{
	m->dbCollective.select(tags(), from(), to());
}

void HistoryModel::confirmUpdateFinished()
{
	if (!m->dbCollective.busy())
		emit updateFinished();
}

void HistoryModel::setBegin(const QDateTime & begin)
{
	if (m->begin != begin) {
		m->begin = begin;
		emit beginChanged();
	}
}

void HistoryModel::setEnd(const QDateTime & end)
{
	if (m->end != end) {
		m->end = end;
		emit endChanged();
	}
}

void HistoryModel::onSchemaChanged()
{
	m->dbCollective.setSchema(schema());
}

void HistoryModel::onSelected(internal::HistoryCollective::ColumnValues columnValues, QDateTime minOpenTime, QDateTime maxCloseTime)
{
	setBegin(minOpenTime);
	setEnd(maxCloseTime);

	internal::ModelMixin<HistoryModel>::onSelected(columnValues);
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
