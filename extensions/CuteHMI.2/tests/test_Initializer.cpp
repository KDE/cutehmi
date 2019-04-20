#include "../cutehmi.init.cpp"

#include <QtTest/QtTest>

namespace cutehmi {

class test_Initializer:
	public QObject
{
	Q_OBJECT

	private slots:
		void metaTypes();
};

void test_Initializer::metaTypes()
{
	QVERIFY(QMetaType::type("cutehmi::ErrorInfo") != QMetaType::UnknownType);
}

}

QTEST_MAIN(cutehmi::test_Initializer)
#include "test_Initializer.moc"

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
