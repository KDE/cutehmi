#include "../../include/cutehmi/Notification.hpp"
#include "../../include/cutehmi/Notifier.hpp"

namespace cutehmi {

Notification::Notification(Type type, const QString & text, QObject * parent):
	QObject(parent),
	m(new Members{type, text, QDateTime::currentDateTime()})
{
}

void Notification::Info(const QString & text)
{
	Notification notification(Notification::INFO, text);
	Notifier::Instance().add(& notification);
}

void Notification::Warning(const QString & text)
{
	Notification notification(Notification::WARNING, text);
	Notifier::Instance().add(& notification);
}

void Notification::Critical(const QString & text)
{
	Notification notification(Notification::CRITICAL, text);
	Notifier::Instance().add(& notification);
}

void Notification::Critical(const ErrorInfo & errorInfo)
{
	return Critical(errorInfo.toString());
}

Notification::Type Notification::type() const
{
	return m->type;
}

void Notification::setType(Type type)
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

const QDateTime & Notification::dateTime() const
{
	return m->dateTime;
}

std::unique_ptr<Notification> Notification::clone() const
{
	std::unique_ptr<Notification> clone(new Notification);
	*(clone->m) = *m;
	return clone;
}

}

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
