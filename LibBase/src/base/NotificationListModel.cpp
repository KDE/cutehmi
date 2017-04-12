#include "../../include/base/NotificationListModel.hpp"

namespace cutehmi {
namespace base {

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

	return QVariant();
}

void NotificationListModel::prepend(std::unique_ptr<Notification> notification)
{
	beginInsertRows(QModelIndex(), 0, 0);
	m->notifications.prepend(notification.release());
	endInsertRows();
}

void NotificationListModel::removeLast(int num)
{
	CUTEHMI_BASE_ASSERT(num >= 0, QString("parameter value must be non-negative (given '%1')").arg(num).toLocal8Bit().constData());

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
}
