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

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
