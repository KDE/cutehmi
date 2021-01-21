#include <cutehmi/lockscreen/Gatekeeper.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace lockscreen {

class test_Gatekeeper:
	public QObject
{
		Q_OBJECT

	private slots:
		void initTestCase();

		void pickNumberOfHashes();

		void authenticate();

	private:
		std::unique_ptr<Gatekeeper> m_gatekeeper;
};

void test_Gatekeeper::initTestCase()
{
	m_gatekeeper = std::make_unique<Gatekeeper>();
}

void test_Gatekeeper::pickNumberOfHashes()
{
	int low = cutehmi::test::rand<int>();
	int high = cutehmi::test::rand<int>();

	CUTEHMI_INFO("Warnings are OK, if random number is out of range. Gatekeeper should sanitize wrong values.");
	m_gatekeeper->setHashesLow(low);
	m_gatekeeper->setHashesHigh(high);

	int numberOfHashes = m_gatekeeper->pickNumberOfHashes();

	QVERIFY2(numberOfHashes >= m_gatekeeper->hashesLow(), qPrintable(QString("returned value: %1, given lower bound: %2").arg(numberOfHashes).arg(m_gatekeeper->hashesLow())));
	QVERIFY2(numberOfHashes <= m_gatekeeper->hashesHigh(), qPrintable(QString("returned value: %1, given upper bound: %2").arg(numberOfHashes).arg(m_gatekeeper->hashesHigh())));
}

void test_Gatekeeper::authenticate()
{
	// Pick some reasonable amount of hashes.
	int low = cutehmi::test::rand<int>(1000, 10000);
	int high = cutehmi::test::rand<int>(low, 10000);

	m_gatekeeper->setHashesLow(low);
	m_gatekeeper->setHashesHigh(high);

	m_gatekeeper->setSecret(QByteArray());
	QVERIFY(m_gatekeeper->authenticate());

	QString password = cutehmi::test::rand<QString>();
	m_gatekeeper->setPassword(password);
	QByteArray secret = m_gatekeeper->makeSecret(password);
	m_gatekeeper->setSecret(secret);
	QVERIFY(m_gatekeeper->authenticate());

	// Get rid of improbable, but possible collision.
	do {
		password = cutehmi::test::rand<QString>();
	} while (m_gatekeeper->makeSecret(password) == m_gatekeeper->secret());
	m_gatekeeper->setPassword(password);
	QVERIFY(!m_gatekeeper->authenticate());
}

}
}

QTEST_MAIN(cutehmi::lockscreen::test_Gatekeeper)
#include "test_Gatekeeper.moc"
