#include <QtTest/QtTest>
#include <QProcess>

#include <cutehmi/console/autogen/cutehmi.dirs.hpp>

namespace cutehmi {
namespace console {

class test_cutehmi_console:
	public QObject
{
		Q_OBJECT

	private slots:
		void initTestCase();

		void helpOption();

		void versionOption();

	private:
		QString m_installDir;
		QString m_programPath;
};

void test_cutehmi_console::initTestCase()
{
	m_installDir = qEnvironmentVariable("CUTEHMI_INSTALL_DIR");
	QVERIFY(!m_installDir.isEmpty());

	QString toolsInstallSubdir = CUTEHMI_DIRS_TOOLS_INSTALL_SUBDIR;
	m_programPath = m_installDir;
	if (!toolsInstallSubdir.isEmpty())
		m_programPath += "/" + toolsInstallSubdir;
	m_programPath +=  "/cutehmi.console.0";
#ifndef CUTEHMI_NDEBUG
	m_programPath += ".debug";
#endif
}

void test_cutehmi_console::helpOption()
{
	QList<QStringList> argumentsList;
	argumentsList << QStringList({"--help"})
			<< QStringList({"--h"});

	for (auto && arguments : argumentsList) {
		QProcess process;
		process.start(m_programPath, arguments);
		process.waitForFinished(1000);
		QCOMPARE(process.error(), QProcess::UnknownError);
		QVERIFY(!process.readAllStandardError().contains("Unknown option"));
		QVERIFY(!process.readAllStandardOutput().isEmpty());
		QCOMPARE(process.exitStatus(), QProcess::NormalExit);
		QCOMPARE(process.exitCode(), EXIT_SUCCESS);
	}
}

void test_cutehmi_console::versionOption()
{
	QList<QStringList> argumentsList;
	argumentsList << QStringList({"--version"})
			<< QStringList({"--v"});

	for (auto && arguments : argumentsList) {
		QProcess process;
		process.start(m_programPath, arguments);
		process.waitForFinished(1000);
		QCOMPARE(process.error(), QProcess::UnknownError);
		QVERIFY(!process.readAllStandardError().contains("Unknown option"));
		QVERIFY(!process.readAllStandardOutput().isEmpty());
		QCOMPARE(process.exitStatus(), QProcess::NormalExit);
		QCOMPARE(process.exitCode(), EXIT_SUCCESS);
	}
}

}
}

QTEST_MAIN(cutehmi::console::test_cutehmi_console)
#include "test_cutehmi_console.moc"

//(c)C: Copyright © 2020-2024, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
