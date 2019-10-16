#include <cutehmi/modbus/logging.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace modbus {

class test_logging:
	public QObject
{
	Q_OBJECT

	private slots:
		void loggingCategory();
};

void test_logging::loggingCategory()
{
	QCOMPARE(cutehmi::modbus::loggingCategory().categoryName(), "cutehmi_modbus_2");
}

}
}

QTEST_MAIN(cutehmi::modbus::test_logging)
#include "test_logging.moc"
