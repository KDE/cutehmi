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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
