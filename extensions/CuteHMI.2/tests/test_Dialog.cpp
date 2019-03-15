#include <cutehmi/Dialog.hpp>
#include <cutehmi/Dialogist.hpp>

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

		void Info();

		void Warning();

		void Question();

		void Critical();
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
	dialog.setType(Dialog::INFO);
	QCOMPARE(dialog.type(), Dialog::INFO);
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

void test_Dialog::Info()
{
	try {
		std::unique_ptr<Dialog> dialog = Dialog::Info("Info.");
		QCOMPARE(dialog->type(), Dialog::INFO);
		QCOMPARE(dialog->text(), "Info.");
		QCOMPARE(dialog->buttons(), Dialog::BUTTON_OK);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}
}

void test_Dialog::Warning()
{
	try {
		std::unique_ptr<Dialog> dialog = Dialog::Warning("Warning.");
		QCOMPARE(dialog->type(), Dialog::WARNING);
		QCOMPARE(dialog->text(), "Warning.");
		QCOMPARE(dialog->buttons(), Dialog::BUTTON_OK);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}
}

void test_Dialog::Question()
{
	try {
		std::unique_ptr<Dialog> dialog = Dialog::Question("Question?");
		QCOMPARE(dialog->type(), Dialog::QUESTION);
		QCOMPARE(dialog->text(), "Question?");
		QCOMPARE(dialog->buttons(), Dialog::BUTTON_YES | Dialog::BUTTON_NO);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}
}

void test_Dialog::Critical()
{
	try {
		std::unique_ptr<Dialog> dialog = Dialog::Critical("Critical.");
		QCOMPARE(dialog->type(), Dialog::CRITICAL);
		QCOMPARE(dialog->text(), "Critical.");
		QCOMPARE(dialog->buttons(), Dialog::BUTTON_OK);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}

	try {
		ErrorInfo err{1, "class", "Error."};
		std::unique_ptr<Dialog> dialog2 = Dialog::Critical(err);
		QCOMPARE(dialog2->type(), Dialog::CRITICAL);
		QCOMPARE(dialog2->text(), err.toString());
		QCOMPARE(dialog2->buttons(), Dialog::BUTTON_OK);
	} catch (const Dialogist::NoAdvertiserException & ) {
	}
}

}

QTEST_MAIN(cutehmi::test_Dialog)
#include "test_Dialog.moc"
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
