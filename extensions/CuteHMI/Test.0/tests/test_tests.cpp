#include <cutehmi/test/tests.hpp>

#include <QtTest/QtTest>

#include <array>

namespace cutehmi {
namespace test {

template <typename T>
struct NumericMock
{
	T m_val;

	T val() const
	{
		return m_val;
	}

	void setVal(T val)
	{
		m_val = val;
	}
};

struct BoolMock
{
	bool m_val;

	bool val() const
	{
		return m_val;
	}

	void setVal(bool val)
	{
		m_val = val;
	}
};

struct QStringMock
{
	QString m_val;

	QString val() const
	{
		return m_val;
	}

	void setVal(const QString & val)
	{
		m_val = val;
	}
};

struct QStringListMock
{
	QStringList m_val;

	QStringList val() const
	{
		return m_val;
	}

	void setVal(const QStringList & val)
	{
		m_val = val;
	}
};

class test_tests:
	public QObject
{
	Q_OBJECT

	private slots:
		void testAccessors();

		void arrEqual();
};

template <typename T>
void testNumericAccessors()
{
	NumericMock<T> mock;

	cutehmi::test::testAccessors(& NumericMock<T>::val, & NumericMock<T>::setVal);
	cutehmi::test::testAccessors(& NumericMock<T>::val, & NumericMock<T>::setVal, mock);
}

void test_tests::testAccessors()
{
	testNumericAccessors<short>();
	testNumericAccessors<int>();
	testNumericAccessors<long>();
	testNumericAccessors<long long>();
	testNumericAccessors<unsigned short>();
	testNumericAccessors<unsigned int>();
	testNumericAccessors<unsigned long>();
	testNumericAccessors<unsigned long long>();
	testNumericAccessors<float>();
	testNumericAccessors<double>();
	testNumericAccessors<long double>();

	{
		BoolMock mock;

		cutehmi::test::testAccessors(& BoolMock::val, & BoolMock::setVal);
		cutehmi::test::testAccessors(& BoolMock::val, & BoolMock::setVal, mock);
	}

	{
		QStringMock mock;

		cutehmi::test::testAccessors(& QStringMock::val, & QStringMock::setVal);
		cutehmi::test::testAccessors(& QStringMock::val, & QStringMock::setVal, mock);
	}

	{
		QStringListMock mock;

		cutehmi::test::testAccessors(& QStringListMock::val, & QStringListMock::setVal);
		cutehmi::test::testAccessors(& QStringListMock::val, & QStringListMock::setVal, mock);
	}
}

void test_tests::arrEqual()
{
	static constexpr int SIZE = 10;

	std::array<int, SIZE> arr;

	cutehmi::test::rand(arr.data(), 10);
	QVERIFY(cutehmi::test::arrEqual(arr.data(), arr.data(), SIZE));
	QVERIFY(!cutehmi::test::arrInequal(arr.data(), arr.data(), SIZE));

	std::array<int, SIZE> arrCopy;
	arrCopy = arr;
	for (std::size_t i = 0; i < SIZE; i++)
		arrCopy[i]++;
	QVERIFY(!cutehmi::test::arrEqual(arr.data(), arrCopy.data(), SIZE));
	QVERIFY(cutehmi::test::arrInequal(arr.data(), arrCopy.data(), SIZE));

	arrCopy = arr;
	for (std::size_t i = 0; i < SIZE; i++)
		arrCopy[i]++;
	arrCopy[SIZE - 1] = arr[SIZE - 1];
	QVERIFY(!cutehmi::test::arrEqual(arr.data(), arrCopy.data(), SIZE));
	QVERIFY(!cutehmi::test::arrInequal(arr.data(), arrCopy.data(), SIZE));

	arr.fill(0);
	QVERIFY(cutehmi::test::arrEqual(arr.data(), 0, SIZE));
	QVERIFY(!cutehmi::test::arrInequal(arr.data(), 0, SIZE));
	QVERIFY(!cutehmi::test::arrEqual(arr.data(), 1, SIZE));
	QVERIFY(cutehmi::test::arrInequal(arr.data(), 1, SIZE));
}

}
}

QTEST_MAIN(cutehmi::test::test_tests)
#include "test_tests.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
