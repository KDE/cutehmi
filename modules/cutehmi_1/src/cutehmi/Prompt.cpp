#include "../../include/cutehmi/Prompt.hpp"
#include "../../include/cutehmi/CuteHMI.hpp"

#include <QEventLoop>
#include <QMutexLocker>

namespace cutehmi {

Prompt::Prompt(Type type, const QString & text, Buttons buttons, QObject * parent):
	QObject(parent),
	m(new Members{type, text, {}, {}, buttons, NO_BUTTON})
{
}

Prompt::Prompt(Type type, const QString & text, const QString & informativeText, Buttons buttons, QObject * parent):
	QObject(parent),
	m(new Members{type, text, informativeText, {}, buttons, NO_BUTTON})
{
}

Prompt::Prompt(Type type, const QString & text, const QString & informativeText, const QString & detailedText, Buttons buttons, QObject * parent):
	QObject(parent),
	m(new Members{type, text, informativeText, detailedText, buttons, NO_BUTTON})
{
}

std::unique_ptr<Prompt> Prompt::Note(const QString & text, Buttons buttons)
{
	std::unique_ptr<Prompt> result(new Prompt(NOTE, text, buttons));
	CuteHMI::Instance().popupBridge()->advertise(result.get());
	return result;
}

std::unique_ptr<Prompt> Prompt::Warning(const QString & text, Buttons buttons)
{
	std::unique_ptr<Prompt> result(new Prompt(WARNING, text, buttons));
	CuteHMI::Instance().popupBridge()->advertise(result.get());
	return result;
}

std::unique_ptr<Prompt> Prompt::Question(const QString & text, Buttons buttons)
{
	std::unique_ptr<Prompt> result(new Prompt(QUESTION, text, buttons));
	CuteHMI::Instance().popupBridge()->advertise(result.get());
	return result;
}

std::unique_ptr<Prompt> Prompt::Critical(const QString & text, Buttons buttons)
{
	std::unique_ptr<Prompt> result(new Prompt(CRITICAL, text, buttons));
	CuteHMI::Instance().popupBridge()->advertise(result.get());
	return result;
}

std::unique_ptr<Prompt> Prompt::Critical(const ErrorInfo & errorInfo, Buttons buttons)
{
	return Critical(errorInfo.toString(), buttons);
}

Prompt::Type Prompt::type() const
{
	return m->type;
}

void Prompt::setType(Type type)
{
	if (m->type != type) {
		m->type = type;
		emit typeChanged();
	}
}

QString Prompt::text() const
{
	return m->text;
}

void Prompt::setText(const QString & text)
{
	if (m->text != text) {
		m->text = text;
		emit textChanged();
	}
}

QString Prompt::informativeText() const
{
	return m->informativeText;
}

void Prompt::setInformativeText(const QString & informativeText)
{
	if (m->informativeText != informativeText) {
		m->informativeText = informativeText;
		emit informativeTextChanged();
	}
}

QString Prompt::detailedText() const
{
	return m->detailedText;
}

void Prompt::setDetailedText(const QString & detailedText)
{
	if (m->detailedText != detailedText) {
		m->detailedText = detailedText;
		emit detailedTextChanged();
	}
}

Prompt::Buttons Prompt::buttons() const
{
	return m->buttons;
}

void Prompt::setButtons(Buttons buttons)
{
	if (m->buttons != buttons) {
		m->buttons = buttons;
		emit buttonsChanged();
	}
}

Prompt::Button Prompt::response() const
{
	return m->response;
}

void Prompt::acceptResponse(Button response)
{
	if (m->response != NO_BUTTON)
		CUTEHMI_LOG_WARNING("Response has been already accepted.");
	else {
		m->response = response;
		emit responseArrived(response);
	}
}

std::unique_ptr<Prompt> Prompt::clone() const
{
	std::unique_ptr<Prompt> clone(new Prompt);
	*(clone->m) = *m;
	return clone;
}

Prompt::Button Prompt::exec()
{
	QEventLoop loop;
	QObject::connect(this, & Prompt::responseArrived, & loop, & QEventLoop::quit);
	loop.exec();

	return response();
}

}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
