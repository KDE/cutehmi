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

//(c)C: Copyright © 2019, CuteBOT <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>, Michal Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
