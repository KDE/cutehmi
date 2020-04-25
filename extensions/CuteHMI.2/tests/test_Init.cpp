#include "../cutehmi.init.cpp"

#include <QtTest/QtTest>

namespace cutehmi {

class test_Init:
	public QObject
{
		Q_OBJECT

	private slots:
		void metaTypes();
};

void test_Init::metaTypes()
{
	QVERIFY(QMetaType::type("cutehmi::ErrorInfo") != QMetaType::UnknownType);
	QVERIFY(QMetaType::type("cutehmi::InplaceError") != QMetaType::UnknownType);
	QVERIFY(QMetaType::type("cutehmi::Message::Button") != QMetaType::UnknownType);
}

}

QTEST_MAIN(cutehmi::test_Init)
#include "test_Init.moc"

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
