#include <cutehmi/InplaceError.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class test_InplaceError:
	public QObject
{
	Q_OBJECT

	private slots:
		void macro();

		void str();
};

void test_InplaceError::macro()
{
	InplaceError err = CUTEHMI_ERROR("Error message.");
	QCOMPARE(err.message, "Error message.");
	QCOMPARE(err.file, __FILE__);
	QVERIFY(err.line != 0);
	QCOMPARE(err.function, Q_FUNC_INFO);
	QCOMPARE(err.code(), Error::FAIL);
}

void test_InplaceError::str()
{
	int line = __LINE__;
	InplaceError err = InplaceError("Error string.", __FILE__, line, Q_FUNC_INFO);
	QString str = err.str();
	QVERIFY(str.contains("Error string."));
	QVERIFY(str.contains(__FILE__));
	QVERIFY(str.contains(QString::number(line)));
	QVERIFY(str.contains(Q_FUNC_INFO));
}


}

QTEST_MAIN(cutehmi::test_InplaceError)
#include "test_InplaceError.moc"

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
