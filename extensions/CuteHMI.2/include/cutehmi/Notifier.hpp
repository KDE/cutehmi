#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_NOTIFIER_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_NOTIFIER_HPP

#include "internal/common.hpp"
#include "NotificationListModel.hpp"
#include "Singleton.hpp"

#include <QObject>
#include <QMutexLocker>

#include <limits>

namespace cutehmi {

/**
 * %Notifier.
 */
class CUTEHMI_API Notifier:
	public QObject,
	public Singleton<Notifier>
{
	Q_OBJECT

	friend class Singleton<Notifier>;

	public:
		Q_PROPERTY(NotificationListModel * model READ model CONSTANT)
		Q_PROPERTY(int maxNotifications READ maxNotifications WRITE setMaxNotifications NOTIFY maxNotificationsChanged)

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

	protected:
		explicit Notifier(QObject * parent = nullptr);

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
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
