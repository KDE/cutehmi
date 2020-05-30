#include <QtTest/QtTest>
#include <QProcess>

#include "../cutehmi.dirs.hpp"

namespace cutehmi {
namespace cmd {

class test_cutehmi_cmd:
	public QObject
{
		Q_OBJECT

	private slots:
		void initTestCase();

		void helpOption();

		void versionOption();

		void extensionMinorScript();

	private:
		QString m_installDir;
		QString m_programPath;
};

void test_cutehmi_cmd::initTestCase()
{
	m_installDir = qEnvironmentVariable("CUTEHMI_INSTALL_DIR");
	QVERIFY(!m_installDir.isEmpty());

	QString toolsInstallSubdir = CUTEHMI_DIRS_TOOLS_INSTALL_SUBDIR;
	m_programPath = m_installDir;
	if (!toolsInstallSubdir.isEmpty())
		m_programPath += "/" + toolsInstallSubdir;
	m_programPath +=  "/cutehmi.cmd.0";
#ifndef CUTEHMI_NDEBUG
	m_programPath += ".debug";
#endif
}

void test_cutehmi_cmd::helpOption()
{
	QList<QStringList> argumentsList;
	argumentsList << QStringList({"--help"})
			<< QStringList({"--h"});

	for (auto arguments : argumentsList) {
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

void test_cutehmi_cmd::versionOption()
{
	QList<QStringList> argumentsList;
	argumentsList << QStringList({"--version"})
			<< QStringList({"--v"});

	for (auto arguments : argumentsList) {
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

void test_cutehmi_cmd::extensionMinorScript()
{
	QProcess process;

	QStringList arguments;
	arguments << "--extension=CuteHMI.2"
			<< "--minor=0"
			<< "--script=console.info('test')";
	process.start(m_programPath, arguments);
	QVERIFY(process.waitForFinished(1000));
	QCOMPARE(process.error(), QProcess::UnknownError);
	QCOMPARE(process.exitStatus(), QProcess::NormalExit);
	QCOMPARE(process.exitCode(), EXIT_SUCCESS);
}

}
}

QTEST_MAIN(cutehmi::cmd::test_cutehmi_cmd)
#include "test_cutehmi_cmd.moc"

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
