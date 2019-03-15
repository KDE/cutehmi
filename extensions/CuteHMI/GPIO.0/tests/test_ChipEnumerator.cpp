#include <cutehmi/gpio/ChipEnumerator.hpp>

#include <QtTest/QtTest>

namespace cutehmi {
namespace gpio {

class test_ChipEnumerator:
	public QObject
{
	Q_OBJECT

	private slots:
		void update();
};

void test_ChipEnumerator::update()
{
	ChipEnumerator::Instance().update();
}

}
}

QTEST_MAIN(cutehmi::gpio::test_ChipEnumerator)
#include "test_ChipEnumerator.moc"
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
