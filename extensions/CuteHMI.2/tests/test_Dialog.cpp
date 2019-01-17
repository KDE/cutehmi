#include <cutehmi/Dialog.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>
#include <QSignalSpy>

namespace cutehmi {

class test_Dialog:
	public QObject
{
	Q_OBJECT

	private slots:
		void initTestCase();

		void properties();

		void response();

		void clone();
};

void test_Dialog::initTestCase()
{
	qRegisterMetaType<cutehmi::Dialog::Button>();
}

void test_Dialog::properties()
{
	Dialog dialog(Dialog::WARNING, "Text.", "Informative text.", "Detailed text.", Dialog::BUTTON_ABORT);

	QSignalSpy typeSpy(& dialog, & Dialog::typeChanged);
	QCOMPARE(dialog.type(), Dialog::WARNING);
	dialog.setType(Dialog::NOTE);
	QCOMPARE(dialog.type(), Dialog::NOTE);
	QCOMPARE(typeSpy.count(), 1);

	QSignalSpy textSpy(& dialog, & Dialog::textChanged);
	QCOMPARE(dialog.text(), "Text.");
	dialog.setText("Modified text.");
	QCOMPARE(dialog.text(), "Modified text.");
	QCOMPARE(textSpy.count(), 1);

	QSignalSpy informativeTextSpy(& dialog, & Dialog::informativeTextChanged);
	QCOMPARE(dialog.informativeText(), "Informative text.");
	dialog.setInformativeText("Modified informative text.");
	QCOMPARE(dialog.informativeText(), "Modified informative text.");
	QCOMPARE(informativeTextSpy.count(), 1);

	QSignalSpy detailedTextSpy(& dialog, & Dialog::detailedTextChanged);
	QCOMPARE(dialog.detailedText(), "Detailed text.");
	dialog.setDetailedText("Modified detailed text.");
	QCOMPARE(dialog.detailedText(), "Modified detailed text.");
	QCOMPARE(detailedTextSpy.count(), 1);

	QSignalSpy buttonsSpy(& dialog, & Dialog::buttonsChanged);
	QCOMPARE(dialog.buttons(), Dialog::BUTTON_ABORT);
	dialog.setButtons(Dialog::BUTTON_APPLY);
	QCOMPARE(dialog.buttons(), Dialog::BUTTON_APPLY);
	QCOMPARE(buttonsSpy.count(), 1);
}

void test_Dialog::response()
{
	Dialog dialog(Dialog::WARNING, "Text", Dialog::BUTTON_ABORT | Dialog::BUTTON_APPLY);
	QSignalSpy spy(& dialog, & Dialog::responseArrived);

	QCOMPARE(dialog.response(), Dialog::NO_BUTTON);

	dialog.acceptResponse(Dialog::BUTTON_APPLY);
	QCOMPARE(dialog.response(), Dialog::BUTTON_APPLY);
	QCOMPARE(spy.count(), 1);
	QCOMPARE(spy.at(0).at(0).value<Dialog::Button>(), Dialog::BUTTON_APPLY);
	spy.clear();

	dialog.acceptResponse(Dialog::BUTTON_ABORT);
	QCOMPARE(dialog.response(), Dialog::BUTTON_APPLY);
	QCOMPARE(spy.count(), 0);
	spy.clear();

	dialog.acceptResponse(Dialog::NO_BUTTON);
	QCOMPARE(dialog.response(), Dialog::BUTTON_APPLY);
	QCOMPARE(spy.count(), 0);
	spy.clear();

	Dialog dialogAcceptUnavailable(Dialog::WARNING, "Text", Dialog::BUTTON_ABORT | Dialog::BUTTON_APPLY);
	dialogAcceptUnavailable.acceptResponse(Dialog::BUTTON_CANCEL);
	QCOMPARE(dialogAcceptUnavailable.response(), Dialog::BUTTON_CANCEL);
}

void test_Dialog::clone()
{
	Dialog dialog(Dialog::WARNING, "Text.", "Informative text.", "Detailed text.", Dialog::BUTTON_ABORT);
	std::unique_ptr<Dialog> copy = dialog.clone();

	QCOMPARE(dialog.type(), copy->type());
	QCOMPARE(dialog.text(), copy->text());
	QCOMPARE(dialog.informativeText(), copy->informativeText());
	QCOMPARE(dialog.detailedText(), copy->detailedText());
	QCOMPARE(dialog.buttons(), copy->buttons());
}

}

QTEST_MAIN(cutehmi::test_Dialog)
#include "test_Dialog.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
