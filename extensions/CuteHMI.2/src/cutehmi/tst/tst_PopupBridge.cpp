#include <cutehmi/Exception.hpp>

#include <cutehmi/test/random.hpp>

#include <QtTest/QtTest>

namespace cutehmi {

class tst_PopupBridge:
	public QObject
{
	Q_OBJECT

	private slots:
		void what();
};

void tst_PopupBridge::what()
{
}

}

QTEST_MAIN(cutehmi::tst_PopupBridge)
#include "tst_PopupBridge.moc"
