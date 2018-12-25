#include <cutehmi/logging.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class tst_logging:
	public QObject
{
	Q_OBJECT

	private slots:
		void loggingCategory();
};

void tst_logging::loggingCategory()
{
	QCOMPARE(cutehmi::loggingCategory().categoryName(), "CuteHMI.2");
}

}

QTEST_MAIN(cutehmi::tst_logging)
#include "tst_logging.moc"

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
