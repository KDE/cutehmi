#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_NOTIFICATIONLISTMODEL_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_NOTIFICATIONLISTMODEL_HPP

#include "internal/common.hpp"
#include "Notification.hpp"

#include <QAbstractListModel>

namespace cutehmi {
namespace base {

class NotificationListModel:
	public QAbstractListModel
{
	Q_OBJECT
	typedef QAbstractListModel Parent;

	public:
		enum role_t {
			TYPE_ROLE = Qt::UserRole,
			DATE_TIME_ROLE
		};

		NotificationListModel(QObject * parent = 0);

		~NotificationListModel() override;

		int rowCount(const QModelIndex & parent = QModelIndex()) const override;

		QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

		QHash<int, QByteArray> roleNames() const override;

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

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
