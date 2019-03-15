#include <cutehmi/bitcoincash/Address.hpp>

#include <cutehmi/test/tests.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace bitcoincash {

class test_Address:
	public QObject
{
	Q_OBJECT

	private slots:
		void ctor();

		void address();

		void updated();

		void totalReceived();

		void totalSent();

		void balance();

		void unconfirmedBalance();

		void unconfirmedTxAppearances();

		void txAppearances();

		void transactions();

		void legacyAddress();

		void cashAddress();

		void update();

		void updateTest();
};

void test_Address::ctor()
{
	Address address;
	QVERIFY(address.address().isNull());
	QCOMPARE(address.updated(), false);
	QCOMPARE(address.totalReceived(), 0.0);
	QCOMPARE(address.totalSent(), 0.0);
	QCOMPARE(address.balance(), 0.0);
	QCOMPARE(address.unconfirmedBalance(), 0.0);
	QCOMPARE(address.unconfirmedTxApperances(), 0);
	QCOMPARE(address.txAppearances(), 0);
	QVERIFY(address.transactions().isEmpty());
	QVERIFY(address.legacyAddress().isNull());
	QVERIFY(address.cashAddress().isNull());
}

void test_Address::address()
{
	test::testAccessors(& Address::address, & Address::setAddress);
}

void test_Address::updated()
{
	test::testAccessors(& Address::updated, & Address::setUpdated);
}

void test_Address::totalReceived()
{
	test::testAccessors(& Address::totalReceived, & Address::setTotalReceived);
}

void test_Address::totalSent()
{
	test::testAccessors(& Address::totalSent, & Address::setTotalSent);
}

void test_Address::balance()
{
	test::testAccessors(& Address::balance, & Address::setBalance);
}

void test_Address::unconfirmedBalance()
{
	test::testAccessors(& Address::unconfirmedBalance, & Address::setUnconfirmedBalance);
}

void test_Address::unconfirmedTxAppearances()
{
	test::testAccessors(& Address::unconfirmedTxApperances, & Address::setUnconfirmedTxAppearances);
}

void test_Address::txAppearances()
{
	test::testAccessors(& Address::txAppearances, & Address::setTxAppearances);
}

void test_Address::transactions()
{
	test::testAccessors(& Address::transactions, & Address::setTransactions);
}

void test_Address::legacyAddress()
{
	test::testAccessors(& Address::legacyAddress, & Address::setLegacyAddress);
}

void test_Address::cashAddress()
{
	test::testAccessors(& Address::cashAddress, & Address::setCashAddress);
}

void test_Address::update()
{
	Address address;

	// If tests fail for some reason, first check the address on block explorer if its balances haven't been modified.
	address.setAddress("bitcoincash:qrkdpwuv4583x2gmcn0gcykk6fjml5ytnvqc9rq8pe");

	QSignalSpy spy(& address, & Address::updateFinished);
	address.update();
	spy.wait();

	QCOMPARE(address.updated(), true);
	QCOMPARE(address.balance(), 9.901e-05);
	QCOMPARE(address.totalReceived(), 9.901e-05);
	QCOMPARE(address.totalSent(), 0.0);
	QCOMPARE(address.unconfirmedBalance(), 0.0);
	QCOMPARE(address.unconfirmedTxApperances(), 0);
	QCOMPARE(address.txAppearances(), 5);
	QCOMPARE(address.transactions().count(), address.txAppearances());
	QCOMPARE(address.transactions()[0], "10c1576490b7da93a69199e8307429cf27d04e1ff33440d7f6fdb673549fc3cf");
	QCOMPARE(address.transactions()[4], "2785e9afee5f09b9870c8ff59a9537eb4d92db63c373e7a17b9cf4adb85e018d");
	QCOMPARE(address.legacyAddress(), "1NbAXGZiD4kcaCn2KT3Ux3Z6udxUtV87Tm");
	QCOMPARE(address.cashAddress(), "bitcoincash:qrkdpwuv4583x2gmcn0gcykk6fjml5ytnvqc9rq8pe");
}

void test_Address::updateTest()
{
	for (int i = 0; i < 1000; i++)
		update();
}

}
}

QTEST_MAIN(cutehmi::bitcoincash::test_Address)
#include "test_Address.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
