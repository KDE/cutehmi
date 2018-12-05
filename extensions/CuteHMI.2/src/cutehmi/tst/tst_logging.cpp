#include <cutehmi/logging.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class tst_logging:
	public QObject
{
	Q_OBJECT

	private slots:
		void loggingCategory();
};

void tst_logging::loggingCategory()
{
	QCOMPARE(cutehmi::loggingCategory().categoryName(), "CuteHMI.2");
}

}

QTEST_MAIN(cutehmi::tst_logging)
#include "tst_logging.moc"
