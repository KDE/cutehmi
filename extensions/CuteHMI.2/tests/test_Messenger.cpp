#include <cutehmi/Messenger.hpp>
#include <cutehmi/Message.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class test_Messenger:
	public QObject
{
		Q_OBJECT

	private slots:
		void initTestCase();

		void noAdvertiser();

		void advertise();
};

class AdvertiserMock:
	public QObject
{
		Q_OBJECT

	public:
		Message::Button response;

	public slots:
		void createDialog(QVariant message);
};

void test_Messenger::initTestCase()
{
}

void test_Messenger::noAdvertiser()
{
	Message message(Message::INFO, "Message", Message::BUTTON_APPLY | Message::BUTTON_CANCEL);
	try {
		Messenger::Instance().advertise(& message);
	} catch (const Messenger::NoAdvertiserException & e) {
		QCOMPARE(e.message()->type(), Message::INFO);
		QCOMPARE(e.message()->text(), "Message");
		QCOMPARE(e.message()->buttons(), Message::BUTTON_APPLY | Message::BUTTON_CANCEL);
	}
}

void test_Messenger::advertise()
{
	Message message(Message::INFO, "Message", Message::BUTTON_APPLY | Message::BUTTON_CANCEL);
	AdvertiserMock advertiserMock;
	advertiserMock.response = Message::BUTTON_CANCEL;
	Messenger::Instance().resetAdvertiser(& advertiserMock);
	Messenger::Instance().advertise(& message);
	QCOMPARE(message.response(), advertiserMock.response);
}

void AdvertiserMock::createDialog(QVariant message)
{
	Q_UNUSED(message)

	message.value<Message *>()->acceptResponse(response);
}

}

QTEST_MAIN(cutehmi::test_Messenger)
#include "test_Messenger.moc"

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
