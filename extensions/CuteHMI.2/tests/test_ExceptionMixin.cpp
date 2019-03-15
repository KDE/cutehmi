#include <cutehmi/ExceptionMixin.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>
#include <QtConcurrent>

namespace cutehmi {

class TestException:
	public ExceptionMixin<TestException>
{
	public:
		explicit TestException(const QString & message):
			ExceptionMixin<TestException>(message)
		{
		}

		TestException(const TestException & other) = default;

		~TestException() override;
};

TestException::~TestException()
{
}

class test_ExceptionMixin:
	public QObject
{
	Q_OBJECT

	private slots:
		void what();

		void concurrent();
};

void test_ExceptionMixin::what()
{
	try {
		throw TestException("Exception test.");
	} catch (TestException & e) {
		QCOMPARE(e.what(), "Exception test.");
	}

	QString randomString = test::rand<QString>();
	try {
		throw TestException(randomString);
	} catch (TestException & e) {
		QCOMPARE(e.what(), randomString.toLocal8Bit().constData());
	}
}

void test_ExceptionMixin::concurrent()
{
	try {
		int arr[1];
		QtConcurrent::blockingMap(arr, arr + 1, [](int){throw TestException("Exception thrown from QtConcurrent::blockingMap.");});
	} catch (TestException & e) {
		QCOMPARE(e.what(), "Exception thrown from QtConcurrent::blockingMap.");
	}
}

}

QTEST_MAIN(cutehmi::test_ExceptionMixin)
#include "test_ExceptionMixin.moc"

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
