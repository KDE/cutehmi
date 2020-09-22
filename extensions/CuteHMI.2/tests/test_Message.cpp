#include <cutehmi/Message.hpp>
#include <cutehmi/Messenger.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>
#include <QSignalSpy>

namespace cutehmi {

class test_Message:
	public QObject
{
		Q_OBJECT

	private slots:
		void initTestCase();

		void properties();

		void response();

		void clone();

		void Info();

		void Warning();

		void Question();

		void Critical();
};

void test_Message::initTestCase()
{
}

void test_Message::properties()
{
	Message message(Message::WARNING, "Text.", "Informative text.", "Detailed text.", Message::BUTTON_ABORT);

	QSignalSpy typeSpy(& message, & Message::typeChanged);
	QCOMPARE(message.type(), Message::WARNING);
	message.setType(Message::INFO);
	QCOMPARE(message.type(), Message::INFO);
	QCOMPARE(typeSpy.count(), 1);

	QSignalSpy textSpy(& message, & Message::textChanged);
	QCOMPARE(message.text(), "Text.");
	message.setText("Modified text.");
	QCOMPARE(message.text(), "Modified text.");
	QCOMPARE(textSpy.count(), 1);

	QSignalSpy informativeTextSpy(& message, & Message::informativeTextChanged);
	QCOMPARE(message.informativeText(), "Informative text.");
	message.setInformativeText("Modified informative text.");
	QCOMPARE(message.informativeText(), "Modified informative text.");
	QCOMPARE(informativeTextSpy.count(), 1);

	QSignalSpy detailedTextSpy(& message, & Message::detailedTextChanged);
	QCOMPARE(message.detailedText(), "Detailed text.");
	message.setDetailedText("Modified detailed text.");
	QCOMPARE(message.detailedText(), "Modified detailed text.");
	QCOMPARE(detailedTextSpy.count(), 1);

	QSignalSpy buttonsSpy(& message, & Message::buttonsChanged);
	QCOMPARE(message.buttons(), Message::BUTTON_ABORT);
	message.setButtons(Message::BUTTON_APPLY);
	QCOMPARE(message.buttons(), Message::BUTTON_APPLY);
	QCOMPARE(buttonsSpy.count(), 1);
}

void test_Message::response()
{
	Message message(Message::WARNING, "Text", Message::BUTTON_ABORT | Message::BUTTON_APPLY);
	QSignalSpy spy(& message, & Message::responseArrived);

	QCOMPARE(message.response(), Message::NO_BUTTON);

	message.acceptResponse(Message::BUTTON_APPLY);
	QCOMPARE(message.response(), Message::BUTTON_APPLY);
	QCOMPARE(spy.count(), 1);
	QCOMPARE(spy.at(0).at(0).value<Message::Button>(), Message::BUTTON_APPLY);
	spy.clear();

	message.acceptResponse(Message::BUTTON_ABORT);
	QCOMPARE(message.response(), Message::BUTTON_APPLY);
	QCOMPARE(spy.count(), 0);
	spy.clear();

	message.acceptResponse(Message::NO_BUTTON);
	QCOMPARE(message.response(), Message::BUTTON_APPLY);
	QCOMPARE(spy.count(), 0);
	spy.clear();

	Message dialogAcceptUnavailable(Message::WARNING, "Text", Message::BUTTON_ABORT | Message::BUTTON_APPLY);
	dialogAcceptUnavailable.acceptResponse(Message::BUTTON_CANCEL);
	QCOMPARE(dialogAcceptUnavailable.response(), Message::BUTTON_CANCEL);
}

void test_Message::clone()
{
	Message message(Message::WARNING, "Text.", "Informative text.", "Detailed text.", Message::BUTTON_ABORT);
	std::unique_ptr<Message> copy = message.clone();

	QCOMPARE(message.type(), copy->type());
	QCOMPARE(message.text(), copy->text());
	QCOMPARE(message.informativeText(), copy->informativeText());
	QCOMPARE(message.detailedText(), copy->detailedText());
	QCOMPARE(message.buttons(), copy->buttons());
}

void test_Message::Info()
{
	try {
		std::unique_ptr<Message> message = Message::Info("Info.");
		QCOMPARE(message->type(), Message::INFO);
		QCOMPARE(message->text(), "Info.");
		QCOMPARE(message->buttons(), Message::BUTTON_OK);
	} catch (const Messenger::NoAdvertiserException & ) {
	}
}

void test_Message::Warning()
{
	try {
		std::unique_ptr<Message> message = Message::Warning("Warning.");
		QCOMPARE(message->type(), Message::WARNING);
		QCOMPARE(message->text(), "Warning.");
		QCOMPARE(message->buttons(), Message::BUTTON_OK);
	} catch (const Messenger::NoAdvertiserException & ) {
	}
}

void test_Message::Question()
{
	try {
		std::unique_ptr<Message> message = Message::Question("Question?");
		QCOMPARE(message->type(), Message::QUESTION);
		QCOMPARE(message->text(), "Question?");
		QCOMPARE(message->buttons(), Message::BUTTON_YES | Message::BUTTON_NO);
	} catch (const Messenger::NoAdvertiserException & ) {
	}
}

void test_Message::Critical()
{
	try {
		std::unique_ptr<Message> message = Message::Critical("Critical.");
		QCOMPARE(message->type(), Message::CRITICAL);
		QCOMPARE(message->text(), "Critical.");
		QCOMPARE(message->buttons(), Message::BUTTON_OK);
	} catch (const Messenger::NoAdvertiserException & ) {
	}

	try {
		ErrorInfo err{1, "class", "Error."};
		std::unique_ptr<Message> message2 = Message::Critical(err);
		QCOMPARE(message2->type(), Message::CRITICAL);
		QCOMPARE(message2->text(), err.toString());
		QCOMPARE(message2->buttons(), Message::BUTTON_OK);
	} catch (const Messenger::NoAdvertiserException & ) {
	}
}

}

QTEST_MAIN(cutehmi::test_Message)
#include "test_Message.moc"

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
