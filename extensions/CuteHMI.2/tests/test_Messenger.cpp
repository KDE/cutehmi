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
	qRegisterMetaType<cutehmi::Message::Button>();
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

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
