#ifndef NOTIFICATIONMANAGERMODEL_HPP
#define NOTIFICATIONMANAGERMODEL_HPP

#include "internal/common.hpp"
#include "Notification.hpp"

#include <QAbstractListModel>

namespace cutehmi {
namespace base {

class NotificationListModel:
	public QAbstractListModel
{
	Q_OBJECT

	public:
		NotificationListModel(QObject * parent = 0);

		~NotificationListModel() override;

		int rowCount(const QModelIndex & parent = QModelIndex()) const override;

		QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

		void prepend(std::unique_ptr<Notification> notification);

		void removeLast(int num = 1);

		void clear();

	private:
		typedef QList<Notification *> NotificationsContainer;

		struct Members
		{
			NotificationsContainer notifications;
		};

		utils::MPtr<Members> m;
};

}
}

#endif // NOTIFICATIONMANAGERMODEL_HPP
