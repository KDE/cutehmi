#include <cutehmi/gpio/logging.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace gpio {

class test_logging:
	public QObject
{
	Q_OBJECT

	private slots:
		void loggingCategory();
};

void test_logging::loggingCategory()
{
	QCOMPARE(cutehmi::gpio::loggingCategory().categoryName(), "CuteHMI.GPIO.0");
}

}
}

QTEST_MAIN(cutehmi::gpio::test_logging)
#include "test_logging.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
