#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_NOTIFICATIONMANAGER_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_NOTIFICATIONMANAGER_HPP

#include "internal/common.hpp"
#include "NotificationListModel.hpp"

#include <QObject>
#include <QMutexLocker>

#include <limits>

namespace cutehmi {

class CUTEHMI_API NotificationManager:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(NotificationListModel * model READ model CONSTANT)
		Q_PROPERTY(int maxNotifications READ maxNotifications WRITE setMaxNotifications NOTIFY maxNotificationsChanged)

		explicit NotificationManager(QObject * parent = 0);

		NotificationListModel * model() const;

		int maxNotifications() const;

		void setMaxNotifications(int maxNotifications);

	public slots:
		/**
		 * Add notification.
		 * @param notification_l notification to add. Parameter will be used locally by this function.
		 * It's passed by a pointer instead of a reference for easier integration with QML.
		 *
		 * @threadsafe
		 */
		void add(Notification * notification_l);

		void clear();

	signals:
		void maxNotificationsChanged();

	private:
		struct Members
		{
			std::unique_ptr<NotificationListModel> model {new NotificationListModel};
			QMutex modelMutex {};
			int maxNotifications {std::numeric_limits<int>::max()};
		};

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
