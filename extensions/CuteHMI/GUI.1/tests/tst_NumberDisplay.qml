import QtQuick 2.12
import QtQuick.Controls 2.5
import QtTest 1.2

import CuteHMI.GUI 1.0

Item {
	id: root

	width: childrenRect.width
	height: childrenRect.height

	Column {
		NumberDisplay {
			id: uninitialized
		}

		NumberDisplay {
			id: active

			value: 12.34
			fractionalWidth: 2
			unit: "Pa"
		}

		NumberDisplay {
			id: warning

			warning: true
			value: 2500
			integralWidth: 3
			fractionalWidth: 0
			unit: "kg"
		}

		NumberDisplay {
			id: alarm

			alarm: true
			value: 0
			integralWidth: 2
			fractionalWidth: 2
			unit: "K"
		}
	}

	TestCase {
		name: "NumberDisplay"
		when: windowShown

		function initTestCase() {
		}

		function test_uninitialized() {
			waitForRendering(uninitialized)
			var image = grabImage(uninitialized);
			image.save(docScreenshotsDir + "/NumberDisplay_uninitialized.png")
		}

		function test_active() {
			waitForRendering(active)
			var image = grabImage(active);
			image.save(docScreenshotsDir + "/NumberDisplay_active.png")
		}

		function test_warnig() {
			waitForRendering(warning)
			var image = grabImage(warning);
			image.save(docScreenshotsDir + "/NumberDisplay_warning.png")
		}

		function test_alarm() {
			waitForRendering(alarm)
			var image = grabImage(alarm);
			image.save(docScreenshotsDir + "/NumberDisplay_alarm.png")
		}
	}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
