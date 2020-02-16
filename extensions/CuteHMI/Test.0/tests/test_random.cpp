#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>


namespace cutehmi {
namespace test {

class test_random:
	public QObject
{
		Q_OBJECT

	private slots:
		void randQString();

		void randQStringList();

		void randPickDouble_data();

		void randPickDouble();
};

void test_random::randQString()
{
	QVERIFY(!cutehmi::test::rand<QString>(cutehmi::test::rand(1, 255)).isEmpty());
}

void test_random::randQStringList()
{
	QVERIFY(!cutehmi::test::rand<QStringList>(cutehmi::test::rand(1, 255)).isEmpty());
}

void test_random::randPickDouble_data()
{
	QTest::addColumn<double>("min");
	QTest::addColumn<double>("max");

	QTest::newRow("normalized positive interval") << 0.5 << 0.75;
	QTest::newRow("normalized negative interval") << -0.75 << -0.5;
	QTest::newRow("normalized mixed interval") << -0.5 << 0.75;

	QTest::newRow("degenerated positive interval") << 0.5 << 0.5;
	QTest::newRow("degenerated negatvie interval") << -0.5 << -0.5;
	QTest::newRow("degenerated zero interval") << 0.0 << 0.0;
	QTest::newRow("degenerated negative zero interval") << -0.0 << -0.0;
	QTest::newRow("degenerated mixed zero interval with negative lower bound") << -0.0 << 0.0;
	QTest::newRow("degenerated mixed zero interval with negative upper bound") << 0.0 << -0.0;

	QTest::newRow("positive fractions interval") << 0.0 << 1.0;
	QTest::newRow("negative fractions interval") << -1.0 << 0.0;
	QTest::newRow("mixed fractions interval") << -1.0 << 1.0;

	QTest::newRow("extremely small left interval") << std::nextafter(0.0, -1.0) << 0.0;
	QTest::newRow("extremely small right interval") << 0.0 << std::nextafter(0.0, 1.0);
	QTest::newRow("extremely small symmetric interval") << std::nextafter(0.0, -1.0) << std::nextafter(0.0, 1.0);

	QTest::newRow("asymmetric right dominated interval") << std::nextafter(0.0, -1.0) << 100.0;
	QTest::newRow("asymmetric left dominated interval") << -100.0 << std::nextafter(0.0, 1.0);

	QTest::newRow("positive thousand interval") << 0.0 << 1000.0;
	QTest::newRow("negative thousand interval") << -1000.0 << 0.0;
	QTest::newRow("mixed thousand interval") << -1000.0 << 1000.0;

	QTest::newRow("positive hundred to thousand interval") << 100.0 << 1000.0;
	QTest::newRow("negative hundred to thousand interval") << -1000.0 << -100.0;
	QTest::newRow("mixed hundred to thousand interval") << -100.0 << 1000.0;

	QTest::newRow("large 10e100 positive interval") << 0.0 << 10.0e100;
	QTest::newRow("large 10e100 negative interval") << -10.0e100 << 0.0;
	QTest::newRow("large 10e100 mixed interval") << -10.0e100 << 10.0e100;

	QTest::newRow("positive interval limits") << 0.0 << std::numeric_limits<double>::max();
	QTest::newRow("negative interval limits") << std::numeric_limits<double>::lowest() << 0.0;
	QTest::newRow("mixed interval limits") << std::numeric_limits<double>::lowest() << std::numeric_limits<double>::max();

	QTest::newRow("close to positgive limit") << std::nextafter(std::numeric_limits<double>::max(), -1.0) << std::numeric_limits<double>::max();
	QTest::newRow("close to negative limit") << std::numeric_limits<double>::lowest() << std::nextafter(std::numeric_limits<double>::lowest(), 1.0);
}

void test_random::randPickDouble()
{
	QFETCH(double, min);
	QFETCH(double, max);

	double result = cutehmi::test::randPick<double>(min, max);
	QVERIFY2(result >= min && result <= max, QString("min: %1, max: %2, result: %3").arg(min).arg(max).arg(result).toLocal8Bit().constData());
}

}
}

QTEST_MAIN(cutehmi::test::test_random)
#include "test_random.moc"

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>, Yuri Chornoivan <yurchor@ukr.net>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
