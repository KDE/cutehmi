#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace test {

class test_random:
	public QObject
{
	Q_OBJECT

	private slots:
		void rand();
};

void test_random::rand()
{
	QVERIFY(!cutehmi::test::rand<QString>(cutehmi::test::rand(1, 255)).isEmpty());
	QVERIFY(!cutehmi::test::rand<QStringList>(cutehmi::test::rand(1, 255)).isEmpty());
}

}
}

QTEST_MAIN(cutehmi::test::test_random)
#include "test_random.moc"

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
