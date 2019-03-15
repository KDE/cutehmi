#include <cutehmi/gpio/ChipEnumerator.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace gpio {

class test_ChipEnumerator:
	public QObject
{
	Q_OBJECT

	private slots:
		void update();
};

void test_ChipEnumerator::update()
{
	ChipEnumerator::Instance().update();
}

}
}

QTEST_MAIN(cutehmi::gpio::test_ChipEnumerator)
#include "test_ChipEnumerator.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
