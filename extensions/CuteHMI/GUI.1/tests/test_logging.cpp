#include <cutehmi/gui/logging.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace gui {

class test_logging:
	public QObject
{
		Q_OBJECT

	private slots:
		void loggingCategory();
};

void test_logging::loggingCategory()
{
	QCOMPARE(cutehmi::gui::loggingCategory().categoryName(), "CuteHMI.GUI.1");
}

}
}

QTEST_MAIN(cutehmi::gui::test_logging)
#include "test_logging.moc"

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
