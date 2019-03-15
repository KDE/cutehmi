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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
