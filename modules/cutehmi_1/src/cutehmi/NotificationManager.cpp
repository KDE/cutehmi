#include "../../include/cutehmi/NotificationManager.hpp"

namespace cutehmi {

NotificationManager::NotificationManager(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

NotificationListModel * NotificationManager::model() const
{
	return m->model.get();
}

int NotificationManager::maxNotifications() const
{
	return m->maxNotifications;
}

void NotificationManager::setMaxNotifications(int maxNotifications)
{
	if (m->maxNotifications != maxNotifications) {
		m->maxNotifications = maxNotifications;
		if (m->model->rowCount() > maxNotifications)
			m->model->removeLast(m->model->rowCount() - maxNotifications);
		emit maxNotificationsChanged();
	}
}

void NotificationManager::add(Notification * notification_l)
{
	QMutexLocker locker(& m->modelMutex);

#ifdef CUTEHMI_DEBUG
	switch (notification_l->type()) {
		case Notification::NOTE:
			CUTEHMI_LOG_INFO("[NOTIFICATION] " << notification_l->text());
			break;
		case Notification::WARNING:
			CUTEHMI_LOG_WARNING("[NOTIFICATION] " << notification_l->text());
			break;
		case Notification::CRITICAL:
			CUTEHMI_LOG_CRITICAL("[NOTIFICATION] " << notification_l->text());
			break;
		default:
			CUTEHMI_LOG_CRITICAL("Unrecognized code ('" << notification_l->type() << "') of 'Notification::type()'. Assuming 'Notification::CRITICAL'.");
			CUTEHMI_LOG_CRITICAL("[NOTIFICATION] " << notification_l->text());
	}
#endif

	m->model->prepend(notification_l->clone());

	if (m->model->rowCount() > maxNotifications())
		m->model->removeLast();
}

void NotificationManager::clear()
{
	m->model->clear();
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
