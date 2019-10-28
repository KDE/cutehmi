#include <cutehmi/Singleton.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class test_Singleton:
	public QObject
{
	Q_OBJECT

	private slots:
		void initTestCase();

		void InstanceA();

		void DestroyA();

		void DestroyB();

		void destroySingletonInstances();

	public:
		static int InstancesCtr;
		static QString destructionOrder;
};

int test_Singleton::InstancesCtr;
QString test_Singleton::destructionOrder;


class SingletonMockA:
	public Singleton<SingletonMockA>
{
	public:
		SingletonMockA();

		~SingletonMockA() override;
};

class SingletonMockB:
	public Singleton<SingletonMockB>
{
	public:
		SingletonMockB();

		~SingletonMockB() override;

		bool test() const;
};


class SingletonMockC:
	public Singleton<SingletonMockC>
{
	public:
		SingletonMockC();

		~SingletonMockC() override;
};

class SingletonMockD:
	public Singleton<SingletonMockD>
{
	public:
		SingletonMockD();

		~SingletonMockD() override;
};


void test_Singleton::initTestCase()
{
	InstancesCtr = 0;
}

void test_Singleton::InstanceA()
{
	QVERIFY(InstancesCtr == 0);

	// Test if Instance() is returning a reference to the same object.
	QCOMPARE(& SingletonMockA::Instance(), & SingletonMockA::Instance());

	// Check if constructor has been called.
	QCOMPARE(InstancesCtr, 1);
}

void test_Singleton::DestroyA()
{
	QVERIFY(InstancesCtr == 1);

	SingletonMockA::Destroy();

	QCOMPARE(InstancesCtr, 0);
}

void test_Singleton::DestroyB()
{
	QVERIFY(InstancesCtr == 0);

	SingletonMockB::Destroy();

	QCOMPARE(InstancesCtr, 0);
}

void test_Singleton::destroySingletonInstances()
{
	QVERIFY(InstancesCtr == 0);
	QVERIFY(destructionOrder.isEmpty());

	SingletonMockC::Instance();
	SingletonMockD::Instance();

	QCOMPARE(InstancesCtr, 2);

	::cutehmi::destroySingletonInstances();

	QCOMPARE(InstancesCtr, 0);
	QCOMPARE(destructionOrder, "DC");
}


SingletonMockA::SingletonMockA()
{
	test_Singleton::InstancesCtr++;
}

SingletonMockA::~SingletonMockA()
{
	test_Singleton::InstancesCtr--;
}


SingletonMockB::SingletonMockB()
{
	test_Singleton::InstancesCtr++;
}

SingletonMockB::~SingletonMockB()
{
	QVERIFY(Instance().test()); // Check if CuteHMI-2.workaround is working.
	test_Singleton::InstancesCtr--;
}

bool SingletonMockB::test() const
{
	return true;
}


SingletonMockC::SingletonMockC()
{
	test_Singleton::InstancesCtr++;
}

SingletonMockC::~SingletonMockC()
{
	test_Singleton::destructionOrder.append('C');
	test_Singleton::InstancesCtr--;
}


SingletonMockD::SingletonMockD()
{
	test_Singleton::InstancesCtr++;
}

SingletonMockD::~SingletonMockD()
{
	test_Singleton::destructionOrder.append('D');
	test_Singleton::InstancesCtr--;
}

}

QTEST_MAIN(cutehmi::test_Singleton)
#include "test_Singleton.moc"

//(c)C: Copyright © 2019, CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
