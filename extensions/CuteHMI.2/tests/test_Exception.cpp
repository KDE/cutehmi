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
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
