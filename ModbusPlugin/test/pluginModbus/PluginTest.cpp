#include "PluginTest.hpp"
#include "../src/pluginModbus/Plugin.hpp"

#include <QTest>

namespace cutehmi {
namespace pluginModbus {

void PluginTest::initTestCase()
{
}

void PluginTest::secUsecFromString()
{
	Plugin plugin;
	unsigned long sec, usec;

	QString str("1.0");
	plugin.secUsecFromString(str, sec, usec);
	QCOMPARE(sec, 1ul);
	QCOMPARE(usec, 0ul);

	str = "0.5";
	plugin.secUsecFromString(str, sec, usec);
	QCOMPARE(sec, 0ul);
	QCOMPARE(usec, 500000ul);

	str = "123.05";
	plugin.secUsecFromString(str, sec, usec);
	QCOMPARE(sec, 123ul);
	QCOMPARE(usec, 50000ul);

	str = "0.999999";
	plugin.secUsecFromString(str, sec, usec);
	QCOMPARE(sec, 0ul);
	QCOMPARE(usec, 999999ul);

	str = "0.000001";
	plugin.secUsecFromString(str, sec, usec);
	QCOMPARE(sec, 0ul);
	QCOMPARE(usec, 1ul);
}

}
}

QTEST_MAIN(cutehmi::pluginModbus::PluginTest)
#include "../../moc/moc_PluginTest.cpp"
