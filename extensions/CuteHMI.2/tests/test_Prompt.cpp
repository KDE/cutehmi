#include <cutehmi/Prompt.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>
#include <QSignalSpy>

namespace cutehmi {

class test_Prompt:
	public QObject
{
	Q_OBJECT

	private slots:
		void initTestCase();

		void properties();

		void response();

		void clone();
};

void test_Prompt::initTestCase()
{
	qRegisterMetaType<cutehmi::Prompt::Button>();
}

void test_Prompt::properties()
{
	Prompt prompt(Prompt::WARNING, "Text.", "Informative text.", "Detailed text.", Prompt::BUTTON_ABORT);

	QSignalSpy typeSpy(& prompt, & Prompt::typeChanged);
	QCOMPARE(prompt.type(), Prompt::WARNING);
	prompt.setType(Prompt::NOTE);
	QCOMPARE(prompt.type(), Prompt::NOTE);
	QCOMPARE(typeSpy.count(), 1);

	QSignalSpy textSpy(& prompt, & Prompt::textChanged);
	QCOMPARE(prompt.text(), "Text.");
	prompt.setText("Modified text.");
	QCOMPARE(prompt.text(), "Modified text.");
	QCOMPARE(textSpy.count(), 1);

	QSignalSpy informativeTextSpy(& prompt, & Prompt::informativeTextChanged);
	QCOMPARE(prompt.informativeText(), "Informative text.");
	prompt.setInformativeText("Modified informative text.");
	QCOMPARE(prompt.informativeText(), "Modified informative text.");
	QCOMPARE(informativeTextSpy.count(), 1);

	QSignalSpy detailedTextSpy(& prompt, & Prompt::detailedTextChanged);
	QCOMPARE(prompt.detailedText(), "Detailed text.");
	prompt.setDetailedText("Modified detailed text.");
	QCOMPARE(prompt.detailedText(), "Modified detailed text.");
	QCOMPARE(detailedTextSpy.count(), 1);

	QSignalSpy buttonsSpy(& prompt, & Prompt::buttonsChanged);
	QCOMPARE(prompt.buttons(), Prompt::BUTTON_ABORT);
	prompt.setButtons(Prompt::BUTTON_APPLY);
	QCOMPARE(prompt.buttons(), Prompt::BUTTON_APPLY);
	QCOMPARE(buttonsSpy.count(), 1);
}

void test_Prompt::response()
{
	Prompt prompt(Prompt::WARNING, "Text", Prompt::BUTTON_ABORT | Prompt::BUTTON_APPLY);
	QSignalSpy spy(& prompt, & Prompt::responseArrived);

	QCOMPARE(prompt.response(), Prompt::NO_BUTTON);

	prompt.acceptResponse(Prompt::BUTTON_APPLY);
	QCOMPARE(prompt.response(), Prompt::BUTTON_APPLY);
	QCOMPARE(spy.count(), 1);
	QCOMPARE(spy.at(0).at(0).value<Prompt::Button>(), Prompt::BUTTON_APPLY);
	spy.clear();

	prompt.acceptResponse(Prompt::BUTTON_ABORT);
	QCOMPARE(prompt.response(), Prompt::BUTTON_APPLY);
	QCOMPARE(spy.count(), 0);
	spy.clear();

	prompt.acceptResponse(Prompt::NO_BUTTON);
	QCOMPARE(prompt.response(), Prompt::BUTTON_APPLY);
	QCOMPARE(spy.count(), 0);
	spy.clear();

	Prompt promptAcceptUnavailable(Prompt::WARNING, "Text", Prompt::BUTTON_ABORT | Prompt::BUTTON_APPLY);
	promptAcceptUnavailable.acceptResponse(Prompt::BUTTON_CANCEL);
	QCOMPARE(promptAcceptUnavailable.response(), Prompt::BUTTON_CANCEL);
}

void test_Prompt::clone()
{
	Prompt prompt(Prompt::WARNING, "Text.", "Informative text.", "Detailed text.", Prompt::BUTTON_ABORT);
	std::unique_ptr<Prompt> copy = prompt.clone();

	QCOMPARE(prompt.type(), copy->type());
	QCOMPARE(prompt.text(), copy->text());
	QCOMPARE(prompt.informativeText(), copy->informativeText());
	QCOMPARE(prompt.detailedText(), copy->detailedText());
	QCOMPARE(prompt.buttons(), copy->buttons());
}

}

QTEST_MAIN(cutehmi::test_Prompt)
#include "test_Prompt.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
