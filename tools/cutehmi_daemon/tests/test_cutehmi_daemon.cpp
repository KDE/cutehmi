#include <QtTest/QtTest>
#include <QProcess>

namespace cutehmi {
namespace daemon {

class test_cutehmi_daemon:
	public QObject
{
	Q_OBJECT

	private slots:
		void initTestCase();

		void helpOption();

		void versionOption();

		void countDaemonExample();

	private:
		QString m_installRoot;
		QString m_programPath;
};

void test_cutehmi_daemon::initTestCase()
{
	QString m_installRoot = qEnvironmentVariable("CUTEHMI_INSTALL_ROOT");
	QVERIFY(!m_installRoot.isEmpty());

	m_programPath = m_installRoot + "/bin/cutehmi_daemon";
#ifndef CUTEHMI_NDEBUG
	m_programPath += "_debug";
#endif
}

void test_cutehmi_daemon::helpOption()
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

void test_cutehmi_daemon::versionOption()
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

void test_cutehmi_daemon::countDaemonExample()
{
	QProcess process;
	QStringList arguments { {"--app"}, {"--project=examples/CountDaemon/Main.qml"} };
	process.start(m_programPath, arguments);
	process.waitForFinished();

	QString stdOut = QString::fromLocal8Bit(process.readAllStandardOutput());
	QString stdErr = QString::fromLocal8Bit(process.readAllStandardError());

	QVERIFY(!stdErr.contains("Unknown option"));

	{
		QRegExp rx(".*(Project file .* does not exist).*");
		QVERIFY2(!rx.exactMatch(stdErr), rx.cap(1).toLocal8Bit().constData());
	}

	QVERIFY(stdErr.contains("I can count"));

	QCOMPARE(process.error(), QProcess::UnknownError);
	QCOMPARE(process.exitStatus(), QProcess::NormalExit);
	QCOMPARE(process.exitCode(), EXIT_SUCCESS);
}

}
}

QTEST_MAIN(cutehmi::daemon::test_cutehmi_daemon)
#include "test_cutehmi_daemon.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
