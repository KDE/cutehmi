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

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
