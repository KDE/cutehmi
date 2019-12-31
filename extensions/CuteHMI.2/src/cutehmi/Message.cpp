#include "../../include/cutehmi/Message.hpp"
#include "../../include/cutehmi/Messenger.hpp"

#include <QEventLoop>
#include <QMutexLocker>

namespace cutehmi {

std::unique_ptr<Message> Message::Info(const QString & text, Message::Buttons buttons)
{
	std::unique_ptr<Message> result(new Message(Message::INFO, text, buttons));
	Messenger::Instance().advertise(result.get());
	return result;
}

std::unique_ptr<Message> Message::Warning(const QString & text, Message::Buttons buttons)
{
	std::unique_ptr<Message> result(new Message(Message::WARNING, text, buttons));
	Messenger::Instance().advertise(result.get());
	return result;
}

std::unique_ptr<Message> Message::Question(const QString & text, Message::Buttons buttons)
{
	std::unique_ptr<Message> result(new Message(Message::QUESTION, text, buttons));
	Messenger::Instance().advertise(result.get());
	return result;
}

std::unique_ptr<Message> Message::Critical(const QString & text, Message::Buttons buttons)
{
	std::unique_ptr<Message> result(new Message(Message::CRITICAL, text, buttons));
	Messenger::Instance().advertise(result.get());
	return result;
}

std::unique_ptr<Message> Message::Critical(const ErrorInfo & errorInfo, Message::Buttons buttons)
{
	return Critical(errorInfo.toString(), buttons);
}

Message::Message(Type type, const QString & text, Buttons buttons, QObject * parent):
	QObject(parent),
	m(new Members{type, text, {}, {}, buttons, NO_BUTTON})
{
}

Message::Message(Type type, const QString & text, const QString & informativeText, Buttons buttons, QObject * parent):
	QObject(parent),
	m(new Members{type, text, informativeText, {}, buttons, NO_BUTTON})
{
}

Message::Message(Type type, const QString & text, const QString & informativeText, const QString & detailedText, Buttons buttons, QObject * parent):
	QObject(parent),
	m(new Members{type, text, informativeText, detailedText, buttons, NO_BUTTON})
{
}

Message::Type Message::type() const
{
	return m->type;
}

void Message::setType(Type type)
{
	if (m->type != type) {
		m->type = type;
		emit typeChanged();
	}
}

QString Message::text() const
{
	return m->text;
}

void Message::setText(const QString & text)
{
	if (m->text != text) {
		m->text = text;
		emit textChanged();
	}
}

QString Message::informativeText() const
{
	return m->informativeText;
}

void Message::setInformativeText(const QString & informativeText)
{
	if (m->informativeText != informativeText) {
		m->informativeText = informativeText;
		emit informativeTextChanged();
	}
}

QString Message::detailedText() const
{
	return m->detailedText;
}

void Message::setDetailedText(const QString & detailedText)
{
	if (m->detailedText != detailedText) {
		m->detailedText = detailedText;
		emit detailedTextChanged();
	}
}

Message::Buttons Message::buttons() const
{
	return m->buttons;
}

void Message::setButtons(Buttons buttons)
{
	if (m->buttons != buttons) {
		m->buttons = buttons;
		emit buttonsChanged();
	}
}

Message::Button Message::response() const
{
	return m->response;
}

void Message::acceptResponse(Button response)
{
	if (m->response != NO_BUTTON)
		CUTEHMI_WARNING("Ignoring new arrival '" << response << "', as response '" << m->response << "' has been already accepted.");
	else {
		if (!(response & buttons()))
			CUTEHMI_WARNING("Forcibly accepting response '" << response << "', which should not be available.");
		emit responseArrived(response);
		m->response = response;
		emit responseChanged();
	}
}

std::unique_ptr<Message> Message::clone() const
{
	std::unique_ptr<Message> clone(new Message);
	*(clone->m) = *m;
	return clone;
}

Message::Button Message::exec()
{
	QEventLoop loop;
	QObject::connect(this, & Message::responseArrived, & loop, & QEventLoop::quit);
	loop.exec();

	return response();
}

}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
