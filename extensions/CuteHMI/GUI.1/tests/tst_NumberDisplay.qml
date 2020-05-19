import QtQuick 2.12
import QtQuick.Controls 2.5
import QtTest 1.2

import CuteHMI.GUI 1.0

Item {
	id: root

	width: childrenRect.width
	height: childrenRect.height

	Row {
		id: preview

		spacing: 5
		padding: 5

		//! [NumberDisplay preview]
		NumberDisplay {
		}

		NumberDisplay {
			value: 12.34
			fractionalWidth: 2
			unit: "Pa"
		}

		NumberDisplay {
			warning: true
			value: 2500
			integralWidth: 3
			fractionalWidth: 0
			unit: "kg"
		}

		NumberDisplay {
			alarm: true
			value: 0
			integralWidth: 2
			fractionalWidth: 2
			unit: "K"
		}
		//! [NumberDisplay preview]
	}

	TestCase {
		name: "NumberDisplay"
		when: windowShown

		function initTestCase() {
		}

		function test_preview() {
			waitForRendering(preview)
			var image = grabImage(preview);
			image.save(docScreenshotsDir + "/NumberDisplay_preview.png")
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
