#include "../../include/cutehmi/Notifier.hpp"

namespace cutehmi {

Notifier::Notifier(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

NotificationListModel * Notifier::model() const
{
	return m->model.get();
}

int Notifier::maxNotifications() const
{
	return m->maxNotifications;
}

void Notifier::setMaxNotifications(int maxNotifications)
{
	if (m->maxNotifications != maxNotifications) {
		m->maxNotifications = maxNotifications;
		if (m->model->rowCount() > maxNotifications)
			m->model->removeLast(m->model->rowCount() - maxNotifications);
		emit maxNotificationsChanged();
	}
}

void Notifier::add(Notification * notification_l)
{
	QMutexLocker locker(& m->modelMutex);

#ifndef CUTEHMI_NDEBUG
	switch (notification_l->type()) {
		case Notification::INFO:
			CUTEHMI_INFO("[NOTIFICATION] " << notification_l->text());
			break;
		case Notification::WARNING:
			CUTEHMI_WARNING("[NOTIFICATION] " << notification_l->text());
			break;
		case Notification::CRITICAL:
			CUTEHMI_CRITICAL("[NOTIFICATION] " << notification_l->text());
			break;
		default:
			CUTEHMI_CRITICAL("Unrecognized code ('" << notification_l->type() << "') of 'Notification::type()'. Assuming 'Notification::CRITICAL'.");
			CUTEHMI_CRITICAL("[NOTIFICATION] " << notification_l->text());
	}
#endif

	m->model->prepend(notification_l->clone());

	if (m->model->rowCount() > maxNotifications())
		m->model->removeLast();
}

void Notifier::clear()
{
	m->model->clear();
}

}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
