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

	// Using Bitcoin.com test address. If they change anything with it then the tests will fail.
	// So, if tests fail for some reason, don't forget to check https://rest.bitcoin.com/#/address/details/.
	address.setAddress("bitcoincash:qzs02v05l7qs5s24srqju498qu55dwuj0cx5ehjm2c");

	QSignalSpy spy(& address, & Address::updateFinished);
	address.update();
	spy.wait();

	QCOMPARE(address.updated(), true);
	QCOMPARE(address.balance(), 0.02);
	QCOMPARE(address.totalReceived(), 0.06185868);
	QCOMPARE(address.totalSent(), 0.04185868);
	QCOMPARE(address.unconfirmedBalance(), 0.0);
	QCOMPARE(address.unconfirmedTxApperances(), 0);
	QCOMPARE(address.txAppearances(), 37);
	QCOMPARE(address.transactions().count(), address.txAppearances());
	QCOMPARE(address.transactions()[0], "282b3b296b6aed7122586ed69f7a57d35584eaf94a4d1b1ad7d1b05d36cb79d1");
	QCOMPARE(address.transactions()[36], "81039b1d7b855b133f359f9dc65f776bd105650153a941675fedc504228ddbd3");
	QCOMPARE(address.legacyAddress(), "1Fg4r9iDrEkCcDmHTy2T79EusNfhyQpu7W");
	QCOMPARE(address.cashAddress(), "bitcoincash:qzs02v05l7qs5s24srqju498qu55dwuj0cx5ehjm2c");
}

}
}

QTEST_MAIN(cutehmi::bitcoincash::test_Address)
#include "test_Address.moc"

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
