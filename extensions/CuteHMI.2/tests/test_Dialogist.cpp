#include <cutehmi/Dialogist.hpp>
#include <cutehmi/Dialog.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class test_Dialogist:
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
		Dialog::Button response;

	public slots:
		void createDialog(QVariant dialog);
};

void test_Dialogist::initTestCase()
{
	qRegisterMetaType<cutehmi::Dialog::Button>();
}

void test_Dialogist::noAdvertiser()
{
	Dialog dialog(Dialog::INFO, "Message", Dialog::BUTTON_APPLY | Dialog::BUTTON_CANCEL);
	try {
		Dialogist::Instance().advertise(& dialog);
	} catch (const Dialogist::NoAdvertiserException & e) {
		QCOMPARE(e.dialog()->type(), Dialog::INFO);
		QCOMPARE(e.dialog()->text(), "Message");
		QCOMPARE(e.dialog()->buttons(), Dialog::BUTTON_APPLY | Dialog::BUTTON_CANCEL);
	}
}

void test_Dialogist::advertise()
{
	Dialog dialog(Dialog::INFO, "Message", Dialog::BUTTON_APPLY | Dialog::BUTTON_CANCEL);
	AdvertiserMock advertiserMock;
	advertiserMock.response = Dialog::BUTTON_CANCEL;
	Dialogist::Instance().resetAdvertiser(& advertiserMock);
	Dialogist::Instance().advertise(& dialog);
	QCOMPARE(dialog.response(), advertiserMock.response);
}

void AdvertiserMock::createDialog(QVariant dialog)
{
	Q_UNUSED(dialog)

	dialog.value<Dialog *>()->acceptResponse(response);
}

}

QTEST_MAIN(cutehmi::test_Dialogist)
#include "test_Dialogist.moc"

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
