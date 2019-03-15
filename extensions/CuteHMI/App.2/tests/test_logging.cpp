#include <cutehmi/app/logging.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace app {

class test_logging:
	public QObject
{
	Q_OBJECT

	private slots:
		void loggingCategory();
};

void test_logging::loggingCategory()
{
	QCOMPARE(cutehmi::app::loggingCategory().categoryName(), "CuteHMI.App.2");
}

}
}

QTEST_MAIN(cutehmi::app::test_logging)
#include "test_logging.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
