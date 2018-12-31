#include <cutehmi/Exception.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>
#include <QtConcurrent>

namespace cutehmi {

class test_Exception:
	public QObject
{
	Q_OBJECT

	private slots:
		void what();

		void concurrent();
};

void test_Exception::what()
{
	try {
		throw Exception("Exception test.");
	} catch (Exception & e) {
		QCOMPARE(e.what(), "Exception test.");
	}

	QString randomString = test::rand<QString>();
	try {
		throw Exception(randomString);
	} catch (Exception & e) {
		QCOMPARE(e.what(), randomString.toLocal8Bit().constData());
	}
}

void test_Exception::concurrent()
{
	try  {
		int arr[1];
		QtConcurrent::blockingMap(arr, arr + 1, [](int){throw Exception("Exception thrown from QtConcurrent::blockingMap.");});
	} catch (Exception & e) {
		QCOMPARE(e.what(), "Exception thrown from QtConcurrent::blockingMap.");
	}
}

}

QTEST_MAIN(cutehmi::test_Exception)
#include "test_Exception.moc"

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
