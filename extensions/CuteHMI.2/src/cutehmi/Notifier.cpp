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

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, CuteBOT <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
