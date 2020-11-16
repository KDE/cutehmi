#include "../cutehmi.dirs.hpp"

#include <cutehmi/Internationalizer.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class test_Internationalizer:
	public QObject
{
		Q_OBJECT

	private slots:
		void initTestCase();

		void loadTranslation();

		void unloadTranslation();

		void loadQtTranslation();

		void unloadQtTranslation();

		void mixedTranslations();
};

void test_Internationalizer::initTestCase()
{
	QDir toolsDir = QDir::current();
	toolsDir.cd(QDir("/" CUTEHMI_DIRS_TESTS_INSTALL_SUBDIR).relativeFilePath("/" CUTEHMI_DIRS_TOOLS_INSTALL_SUBDIR));
	QDir::setCurrent(toolsDir.absolutePath());
}

void test_Internationalizer::loadTranslation()
{
	Internationalizer & i18ner = Internationalizer::Instance();
	i18ner.setUILanguage("pl_PL");

	i18ner.loadTranslation("CuteHMI.2.test", false);
	QVERIFY(i18ner.m->translators.contains("CuteHMI.2.test"));
	if (i18ner.m->translators.contains("CuteHMI.2.test"))
		QCOMPARE(i18ner.m->translators.value("CuteHMI.2.test")->translate("cutehmi::Error|", "No error."), "Brak błędu.");

	i18ner.loadTranslation("CuteHMI.2.test_Internationalizer");
	QVERIFY(i18ner.m->translators.contains("CuteHMI.2.test_Internationalizer"));
	if (i18ner.m->translators.contains("CuteHMI.2.test_Internationalizer"))
		QCOMPARE(i18ner.m->translators.value("CuteHMI.2.test_Internationalizer")->translate("cutehmi::Error|", "No error."), "Brak błędu.");
}

void test_Internationalizer::unloadTranslation()
{
	Internationalizer & i18ner = Internationalizer::Instance();
	i18ner.setUILanguage("pl_PL");

	i18ner.unloadTranslation("CuteHMI.2.test");
	QVERIFY(!i18ner.m->translators.contains("CuteHMI.2.test"));

	i18ner.unloadTranslation("CuteHMI.2.test_Internationalizer");
	QVERIFY(!i18ner.m->translators.contains("CuteHMI.2.test_Internationalizer"));
}

void test_Internationalizer::loadQtTranslation()
{
	Internationalizer & i18ner = Internationalizer::Instance();
	i18ner.setUILanguage("pl_PL");

	QVERIFY(i18ner.m->qtTranslator == nullptr);
	i18ner.loadQtTranslation();
	QVERIFY(i18ner.m->qtTranslator != nullptr);
}

void test_Internationalizer::unloadQtTranslation()
{
	Internationalizer & i18ner = Internationalizer::Instance();
	i18ner.setUILanguage("pl_PL");

	i18ner.unloadQtTranslation();
	QVERIFY(i18ner.m->qtTranslator == nullptr);
}

void test_Internationalizer::mixedTranslations()
{
	Internationalizer & i18ner = Internationalizer::Instance();

	loadTranslation();
	unloadTranslation();

	loadQtTranslation();
	unloadQtTranslation();

	loadQtTranslation();
	QVERIFY(i18ner.m->qtTranslator != nullptr);
	i18ner.unloadTranslations(false);
	QVERIFY(i18ner.m->qtTranslator != nullptr);
	i18ner.unloadTranslations();
	QVERIFY(i18ner.m->qtTranslator == nullptr);

	loadTranslation();
	loadQtTranslation();
	i18ner.unloadTranslations();	// Should nullify i18ner.m->qtTranslator as well.
	QVERIFY(i18ner.m->qtTranslator == nullptr);
	QVERIFY(i18ner.m->translators.isEmpty());

	i18ner.setUILanguage("no_NO");
	i18ner.loadTranslation("CuteHMI.2.test", false);
	QVERIFY(i18ner.m->translators.contains("CuteHMI.2.test"));
	if (i18ner.m->translators.contains("CuteHMI.2.test"))
		QCOMPARE(i18ner.m->translators.value("CuteHMI.2.test")->translate("cutehmi::Error|", "No error."), "");
	i18ner.setUILanguage("pl_PL");
	if (i18ner.m->translators.contains("CuteHMI.2.test_Internationalizer"))
		QCOMPARE(i18ner.m->translators.value("CuteHMI.2.test_Internationalizer")->translate("cutehmi::Error|", "No error."), "Brak błędu.");
	i18ner.unloadTranslation("CuteHMI.2.test");
	if (i18ner.m->translators.contains("CuteHMI.2.test"))
		QCOMPARE(i18ner.m->translators.value("CuteHMI.2.test")->translate("cutehmi::Error|", "No error."), "");
}

}

QTEST_MAIN(cutehmi::test_Internationalizer)
#include "test_Internationalizer.moc"

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
