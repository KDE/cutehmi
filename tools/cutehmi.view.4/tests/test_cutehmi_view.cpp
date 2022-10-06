#include <QtTest/QtTest>
#include <QProcess>
#include <QScreen>
#include <QPixmap>

#include "../cutehmi.dirs.hpp"

namespace cutehmi {
namespace daemon {

class test_cutehmi_view:
	public QObject
{
		Q_OBJECT

	private slots:
		void initTestCase();

		void helpOption();

		void versionOption();

		void screenshot();

	private:
		QString m_installDir;
		QString m_programPath;
		int m_windowDecorationsWidth;
		int m_windowDecorationsHeight;
};

void test_cutehmi_view::initTestCase()
{
	m_installDir = qEnvironmentVariable("CUTEHMI_INSTALL_DIR");
	QVERIFY(!m_installDir.isEmpty());

	QString toolsInstallSubdir = CUTEHMI_DIRS_TOOLS_INSTALL_SUBDIR;
	m_programPath = m_installDir;
	if (!toolsInstallSubdir.isEmpty())
		m_programPath += "/" + toolsInstallSubdir;
	m_programPath +=  "/cutehmi.view.4";
#ifndef CUTEHMI_NDEBUG
	m_programPath += ".debug";
#endif

	// Using helper window to calculate size of window decorations.
	QWindow helperWindow;
	helperWindow.show();
	m_windowDecorationsWidth = helperWindow.frameGeometry().width() - helperWindow.geometry().width();
	m_windowDecorationsHeight = helperWindow.frameGeometry().height() - helperWindow.geometry().height();
}

void test_cutehmi_view::helpOption()
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

void test_cutehmi_view::versionOption()
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

void test_cutehmi_view::screenshot()
{
	int width = 800;
	int height = 600;

	QStringList arguments;
	QString windowgeometryArg = QString::number(width) + "x" + QString::number(height) + "+0+0";
	arguments << "-qwindowgeometry" << windowgeometryArg << "--lang" << "en_EN";

	QString screenshotPath = m_installDir;
	if (screenshotPath.isEmpty())
		screenshotPath = QDir::temp().path();
	QString artifactsInstallSubdir = CUTEHMI_DIRS_ARTIFACTS_INSTALL_SUBDIR;
	if (!artifactsInstallSubdir.isEmpty())
		screenshotPath += "/" + artifactsInstallSubdir;
	screenshotPath += "/screenshots/" CUTEHMI_DIRS_PROJECT_RELATIVE_PATH "/doc/screenshot.png";
	const char * screenshotFormat = "PNG";

	QProcess process;
	process.start(m_programPath, arguments);
	process.waitForFinished(3500);	// This gives some time for the GUI to show up.

	QScreen * screen = QGuiApplication::primaryScreen();
	if (screen) {
		QPixmap screenshot = screen->grabWindow(0, 0, 0, width + m_windowDecorationsWidth, height + m_windowDecorationsHeight);
		QVERIFY(QDir().mkpath(QFileInfo(screenshotPath).dir().path()));
		QVERIFY(screenshot.save(screenshotPath, screenshotFormat));
	}

	process.terminate();
	process.waitForFinished();
}

}
}

QTEST_MAIN(cutehmi::daemon::test_cutehmi_view)
#include "test_cutehmi_view.moc"

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
