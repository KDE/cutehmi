#include <cutehmi/Initializer.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class InitializerMock:
	public Initializer<InitializerMock>
{
	public:
		InitializerMock();

		static int InitCtr;
		static int DeinitCtr;
		static int CtorCtr;
};

int InitializerMock::InitCtr = 0;
int InitializerMock::DeinitCtr = 0;
int InitializerMock::CtorCtr = 0;

InitializerMock::InitializerMock():
	Initializer<InitializerMock>(
		[]() {
			InitCtr++;
		},
		[]() {
			DeinitCtr++;
		}
	)
{
	CtorCtr++;
}

class test_ExtensionInitializer:
	public QObject
{
	Q_OBJECT

	private slots:
		void instances();
};

void test_ExtensionInitializer::instances()
{
	QVERIFY(InitializerMock::InitCtr == 0);
	QVERIFY(InitializerMock::DeinitCtr == 0);
	QVERIFY(InitializerMock::CtorCtr == 0);

	{
		InitializerMock instance1;
		QCOMPARE(InitializerMock::InitCtr, 1);
		QCOMPARE(InitializerMock::DeinitCtr, 0);
		QCOMPARE(InitializerMock::CtorCtr, 1);

		InitializerMock instance2;
		QCOMPARE(InitializerMock::InitCtr, 1);
		QCOMPARE(InitializerMock::DeinitCtr, 0);
		QCOMPARE(InitializerMock::CtorCtr, 2);
	}

	QCOMPARE(InitializerMock::InitCtr, 1);
	QCOMPARE(InitializerMock::DeinitCtr, 1);
	QCOMPARE(InitializerMock::CtorCtr, 2);
}

}

QTEST_MAIN(cutehmi::test_ExtensionInitializer)
#include "test_ExtensionInitializer.moc"

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
