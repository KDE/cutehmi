import QtQuick 2.12
import QtQuick.Controls 2.5
import QtTest 1.2

//import CuteHMI.GUI 1.0
import CuteHMI.Symbols.HVAC 1.0

Item {
	id: root

	width: childrenRect.width
	height: childrenRect.height

	Flow {
		AirFilter {
			id: inactive

			active: false
			fill: 0.5
		}

		AirFilter {
			id: active

			active: true
			fill: 0.5
		}

		AirFilter {
			id: warning

			warning: true
			fill: 0.5
		}

		AirFilter {
			id: alarm

			alarm: true
			fill: 0.5
		}
	}

	TestCase {
		name: "AirFilter"
		when: windowShown

		function initTestCase() {
		}

		function test_inactive() {
			waitForRendering(inactive)
			var image = grabImage(inactive);
			image.save(docScreenshotsDir + "/AirFilter_inactive.png")
		}

		function test_active() {
			waitForRendering(active)
			var image = grabImage(active);
			image.save(docScreenshotsDir + "/AirFilter_active.png")
		}

		function test_warning() {
			waitForRendering(warning)
			var image = grabImage(warning);
			image.save(docScreenshotsDir + "/AirFilter_warning.png")
		}

		function test_alarm() {
			waitForRendering(alarm)
			var image = grabImage(alarm);
			image.save(docScreenshotsDir + "/AirFilter_alarm.png")
		}
	}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
