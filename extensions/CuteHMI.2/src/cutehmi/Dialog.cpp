#include "../../include/cutehmi/Dialog.hpp"
#include "../../include/cutehmi/Dialogist.hpp"

#include <QEventLoop>
#include <QMutexLocker>

namespace cutehmi {

int Dialog::RegisterButtonMetaType() noexcept
{
	static const int Id = qRegisterMetaType<cutehmi::Dialog::Button>();
	return Id;
}

std::unique_ptr<Dialog> Dialog::Info(const QString & text, Dialog::Buttons buttons)
{
	std::unique_ptr<Dialog> result(new Dialog(Dialog::INFO, text, buttons));
	Dialogist::Instance().advertise(result.get());
	return result;
}

std::unique_ptr<Dialog> Dialog::Warning(const QString & text, Dialog::Buttons buttons)
{
	std::unique_ptr<Dialog> result(new Dialog(Dialog::WARNING, text, buttons));
	Dialogist::Instance().advertise(result.get());
	return result;
}

std::unique_ptr<Dialog> Dialog::Question(const QString & text, Dialog::Buttons buttons)
{
	std::unique_ptr<Dialog> result(new Dialog(Dialog::QUESTION, text, buttons));
	Dialogist::Instance().advertise(result.get());
	return result;
}

std::unique_ptr<Dialog> Dialog::Critical(const QString & text, Dialog::Buttons buttons)
{
	std::unique_ptr<Dialog> result(new Dialog(Dialog::CRITICAL, text, buttons));
	Dialogist::Instance().advertise(result.get());
	return result;
}

std::unique_ptr<Dialog> Dialog::Critical(const ErrorInfo & errorInfo, Dialog::Buttons buttons)
{
	return Critical(errorInfo.toString(), buttons);
}

Dialog::Dialog(Type type, const QString & text, Buttons buttons, QObject * parent):
	QObject(parent),
	m(new Members{type, text, {}, {}, buttons, NO_BUTTON})
{
	RegisterButtonMetaType();
}

Dialog::Dialog(Type type, const QString & text, const QString & informativeText, Buttons buttons, QObject * parent):
	QObject(parent),
	m(new Members{type, text, informativeText, {}, buttons, NO_BUTTON})
{
	RegisterButtonMetaType();
}

Dialog::Dialog(Type type, const QString & text, const QString & informativeText, const QString & detailedText, Buttons buttons, QObject * parent):
	QObject(parent),
	m(new Members{type, text, informativeText, detailedText, buttons, NO_BUTTON})
{
	RegisterButtonMetaType();
}

Dialog::Type Dialog::type() const
{
	return m->type;
}

void Dialog::setType(Type type)
{
	if (m->type != type) {
		m->type = type;
		emit typeChanged();
	}
}

QString Dialog::text() const
{
	return m->text;
}

void Dialog::setText(const QString & text)
{
	if (m->text != text) {
		m->text = text;
		emit textChanged();
	}
}

QString Dialog::informativeText() const
{
	return m->informativeText;
}

void Dialog::setInformativeText(const QString & informativeText)
{
	if (m->informativeText != informativeText) {
		m->informativeText = informativeText;
		emit informativeTextChanged();
	}
}

QString Dialog::detailedText() const
{
	return m->detailedText;
}

void Dialog::setDetailedText(const QString & detailedText)
{
	if (m->detailedText != detailedText) {
		m->detailedText = detailedText;
		emit detailedTextChanged();
	}
}

Dialog::Buttons Dialog::buttons() const
{
	return m->buttons;
}

void Dialog::setButtons(Buttons buttons)
{
	if (m->buttons != buttons) {
		m->buttons = buttons;
		emit buttonsChanged();
	}
}

Dialog::Button Dialog::response() const
{
	return m->response;
}

void Dialog::acceptResponse(Button response)
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

std::unique_ptr<Dialog> Dialog::clone() const
{
	std::unique_ptr<Dialog> clone(new Dialog);
	*(clone->m) = *m;
	return clone;
}

Dialog::Button Dialog::exec()
{
	QEventLoop loop;
	QObject::connect(this, & Dialog::responseArrived, & loop, & QEventLoop::quit);
	loop.exec();

	return response();
}

}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
