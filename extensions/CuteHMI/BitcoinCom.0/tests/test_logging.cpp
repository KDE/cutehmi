#include <cutehmi/bitcoincom/logging.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace bitcoincom {

class test_logging:
	public QObject
{
	Q_OBJECT

	private slots:
		void loggingCategory();
};

void test_logging::loggingCategory()
{
	QCOMPARE(cutehmi::bitcoincom::loggingCategory().categoryName(), "CuteHMI.BitcoinCom.0");
}

}
}

QTEST_MAIN(cutehmi::bitcoincom::test_logging)
#include "test_logging.moc"

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
