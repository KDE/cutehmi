#include "../../include/base/Notification.hpp"
#include "../../include/base/CuteHMI.hpp"

namespace cutehmi {
namespace base {

Notification::Notification(type_t type, const QString & text, QObject * parent):
	QObject(parent),
	m(new Members{type, text})
{
}

void Notification::Note(const QString & text)
{
	Notification notification(Notification::NOTE, text);
	CuteHMI::Instance().notificationManager()->add(& notification);
}

void Notification::Warning(const QString & text)
{
	Notification notification(Notification::WARNING, text);
	CuteHMI::Instance().notificationManager()->add(& notification);
}

void Notification::Critical(const QString & text)
{
	Notification notification(Notification::CRITICAL, text);
	CuteHMI::Instance().notificationManager()->add(& notification);
}

void Notification::Critical(const ErrorInfo & errorInfo)
{
	return Critical(errorInfo.toString());
}

Notification::type_t Notification::type() const
{
	return m->type;
}

void Notification::setType(type_t type)
{
	if (m->type != type) {
		m->type = type;
		emit typeChanged();
	}
}

QString Notification::text() const
{
	return m->text;
}

void Notification::setText(const QString & text)
{
	if (m->text != text) {
		m->text = text;
		emit textChanged();
	}
}

std::unique_ptr<Notification> Notification::clone() const
{
	std::unique_ptr<Notification> clone(new Notification);
	*(clone->m) = *m;
	return std::move(clone);
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
