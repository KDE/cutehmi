#include <QtTest/QtTest>
#include <QProcess>

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

	private:
		QString m_installDir;
		QString m_programPath;
};

void test_cutehmi_view::initTestCase()
{
	QString m_installDir = qEnvironmentVariable("CUTEHMI_INSTALL_DIR");
	QVERIFY(!m_installDir.isEmpty());

	m_programPath = m_installDir + "/bin/cutehmi_view";
#ifndef CUTEHMI_NDEBUG
	m_programPath += "_debug";
#endif
}

void test_cutehmi_view::helpOption()
{
	QList<QStringList> argumentsList;
	argumentsList << QStringList({"--help"})
				  << QStringList({"--h"});

	for (auto arguments: argumentsList) {
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

	for (auto arguments: argumentsList) {
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

QTEST_MAIN(cutehmi::daemon::test_cutehmi_view)
#include "test_cutehmi_view.moc"

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
