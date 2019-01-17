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

		void note();

		void warning();

		void question();

		void critical();
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
	Dialogist dialogist;
	Dialog dialog(Dialog::NOTE, "Message", Dialog::BUTTON_APPLY | Dialog::BUTTON_CANCEL);
	try {
		dialogist.advertise(& dialog);
	} catch (const Dialogist::NoAdvertiserException & e) {
		QCOMPARE(e.dialog()->type(), Dialog::NOTE);
		QCOMPARE(e.dialog()->text(), "Message");
		QCOMPARE(e.dialog()->buttons(), Dialog::BUTTON_APPLY | Dialog::BUTTON_CANCEL);
	}
}

void test_Dialogist::advertise()
{
	Dialogist dialogist;

	Dialog dialog(Dialog::NOTE, "Message", Dialog::BUTTON_APPLY | Dialog::BUTTON_CANCEL);
	AdvertiserMock advertiserMock;
	advertiserMock.response = Dialog::BUTTON_CANCEL;
	dialogist.resetAdvertiser(& advertiserMock);
	dialogist.advertise(& dialog);
	QCOMPARE(dialog.response(), advertiserMock.response);
}

void test_Dialogist::note()
{
	Dialogist dialogist;
	try {
		std::unique_ptr<Dialog> dialog = dialogist.note("Note.");
		QCOMPARE(dialog->type(), Dialog::NOTE);
		QCOMPARE(dialog->text(), "Note.");
		QCOMPARE(dialog->buttons(), Dialog::BUTTON_OK);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}
}

void test_Dialogist::warning()
{
	Dialogist dialogist;
	try {
		std::unique_ptr<Dialog> dialog = dialogist.warning("Warning.");
		QCOMPARE(dialog->type(), Dialog::WARNING);
		QCOMPARE(dialog->text(), "Warning.");
		QCOMPARE(dialog->buttons(), Dialog::BUTTON_OK);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}
}

void test_Dialogist::question()
{
	Dialogist dialogist;
	try {
		std::unique_ptr<Dialog> dialog = dialogist.question("Question?");
		QCOMPARE(dialog->type(), Dialog::QUESTION);
		QCOMPARE(dialog->text(), "Question?");
		QCOMPARE(dialog->buttons(), Dialog::BUTTON_YES | Dialog::BUTTON_NO);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}
}

void test_Dialogist::critical()
{
	Dialogist dialogist;
	try {
		std::unique_ptr<Dialog> dialog = dialogist.critical("Critical.");
		QCOMPARE(dialog->type(), Dialog::CRITICAL);
		QCOMPARE(dialog->text(), "Critical.");
		QCOMPARE(dialog->buttons(), Dialog::BUTTON_OK);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}

	try {
		ErrorInfo err{1, "class", "Error."};
		std::unique_ptr<Dialog> dialog2 = dialogist.critical(err);
		QCOMPARE(dialog2->type(), Dialog::CRITICAL);
		QCOMPARE(dialog2->text(), err.toString());
		QCOMPARE(dialog2->buttons(), Dialog::BUTTON_OK);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}
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
