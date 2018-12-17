#include <cutehmi/PopupBridge.hpp>
#include <cutehmi/Prompt.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class tst_PopupBridge:
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
		Prompt::Button response;

	public slots:
		void createPrompt(QVariant prompt);
};

void tst_PopupBridge::initTestCase()
{
	qRegisterMetaType<cutehmi::Prompt::Button>();
}

void tst_PopupBridge::noAdvertiser()
{
	PopupBridge bridge;
	Prompt prompt(Prompt::NOTE, "Message", Prompt::BUTTON_APPLY | Prompt::BUTTON_CANCEL);
	try {
		bridge.advertise(& prompt);
	} catch (const PopupBridge::NoAdvertiserException & e) {
		QCOMPARE(e.prompt()->type(), Prompt::NOTE);
		QCOMPARE(e.prompt()->text(), "Message");
		QCOMPARE(e.prompt()->buttons(), Prompt::BUTTON_APPLY | Prompt::BUTTON_CANCEL);
	}
}

void tst_PopupBridge::advertise()
{
	PopupBridge bridge;

	Prompt prompt(Prompt::NOTE, "Message", Prompt::BUTTON_APPLY | Prompt::BUTTON_CANCEL);
	AdvertiserMock advertiserMock;
	advertiserMock.response = Prompt::BUTTON_CANCEL;
	bridge.resetAdvertiser(& advertiserMock);
	bridge.advertise(& prompt);
	QCOMPARE(prompt.response(), advertiserMock.response);
}

void tst_PopupBridge::note()
{
	PopupBridge bridge;
	try {
		std::unique_ptr<Prompt> prompt = bridge.note("Note.");
		QCOMPARE(prompt->type(), Prompt::NOTE);
		QCOMPARE(prompt->text(), "Note.");
		QCOMPARE(prompt->buttons(), Prompt::BUTTON_OK);
	} catch (const PopupBridge::NoAdvertiserException & ) {
	}
}

void tst_PopupBridge::warning()
{
	PopupBridge bridge;
	try {
		std::unique_ptr<Prompt> prompt = bridge.warning("Warning.");
		QCOMPARE(prompt->type(), Prompt::WARNING);
		QCOMPARE(prompt->text(), "Warning.");
		QCOMPARE(prompt->buttons(), Prompt::BUTTON_OK);
	} catch (const PopupBridge::NoAdvertiserException & ) {
	}
}

void tst_PopupBridge::question()
{
	PopupBridge bridge;
	try {
		std::unique_ptr<Prompt> prompt = bridge.question("Question?");
		QCOMPARE(prompt->type(), Prompt::QUESTION);
		QCOMPARE(prompt->text(), "Question?");
		QCOMPARE(prompt->buttons(), Prompt::BUTTON_YES | Prompt::BUTTON_NO);
	} catch (const PopupBridge::NoAdvertiserException & ) {
	}
}

void tst_PopupBridge::critical()
{
	PopupBridge bridge;
	try {
		std::unique_ptr<Prompt> prompt = bridge.critical("Critical.");
		QCOMPARE(prompt->type(), Prompt::CRITICAL);
		QCOMPARE(prompt->text(), "Critical.");
		QCOMPARE(prompt->buttons(), Prompt::BUTTON_OK);
	} catch (const PopupBridge::NoAdvertiserException & ) {
	}

	try {
		ErrorInfo err{1, "class", "Error."};
		std::unique_ptr<Prompt> prompt2 = bridge.critical(err);
		QCOMPARE(prompt2->type(), Prompt::CRITICAL);
		QCOMPARE(prompt2->text(), err.toString());
		QCOMPARE(prompt2->buttons(), Prompt::BUTTON_OK);
	} catch (const PopupBridge::NoAdvertiserException & ) {
	}
}

void AdvertiserMock::createPrompt(QVariant prompt)
{
	Q_UNUSED(prompt)

	prompt.value<Prompt *>()->acceptResponse(response);
}

}

QTEST_MAIN(cutehmi::tst_PopupBridge)
#include "tst_PopupBridge.moc"

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
