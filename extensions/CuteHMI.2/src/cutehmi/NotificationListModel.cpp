#include "../../include/cutehmi/NotificationListModel.hpp"

namespace cutehmi {

NotificationListModel::NotificationListModel(QObject * parent):
	QAbstractListModel(parent),
	m(new Members)
{
}

NotificationListModel::~NotificationListModel()
{
	clear();
}

int NotificationListModel::rowCount(const QModelIndex & parent) const
{
	if (parent.isValid())
		return 0;

	return m->notifications.count();
}

QVariant NotificationListModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		 return QVariant();

	if (role == Qt::DisplayRole)
		return m->notifications.at(index.row())->text();

	if (role == TYPE_ROLE)
		return m->notifications.at(index.row())->type();

	if (role == DATE_TIME_ROLE)
		return m->notifications.at(index.row())->dateTime();

	return QVariant();
}

QHash<int, QByteArray> NotificationListModel::roleNames() const
{
	QHash<int, QByteArray> result = Parent::roleNames();
	result[TYPE_ROLE] = "type";
	result[DATE_TIME_ROLE] = "dateTime";
	return result;
}

void NotificationListModel::prepend(std::unique_ptr<Notification> notification)
{
	beginInsertRows(QModelIndex(), 0, 0);
	m->notifications.prepend(notification.release());
	endInsertRows();
}

void NotificationListModel::removeLast(int num)
{
	CUTEHMI_ASSERT(num >= 0, QString("parameter value must be non-negative (given '%1')").arg(num).toLocal8Bit().constData());

	if (num <= 0)
		return;

	beginRemoveRows(QModelIndex(), m->notifications.count() - num, m->notifications.count() - 1);
	while (num > 0) {
		delete m->notifications.takeLast();
		num--;
	}
	endRemoveRows();
}

void NotificationListModel::clear()
{
	if (m->notifications.isEmpty())
		return;

	beginRemoveRows(QModelIndex(), 0, m->notifications.count() - 1);
	while (!m->notifications.isEmpty())
		delete m->notifications.takeFirst();
	endRemoveRows();
}

}

//(c)C: Copyright © 2018-2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
