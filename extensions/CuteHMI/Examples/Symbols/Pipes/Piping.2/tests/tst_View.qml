import QtQuick 2.12
import QtQuick.Controls 2.5
import QtTest 1.2

import CuteHMI.Examples.Symbols.Pipes.Piping 2.0

Item {
	id: root

	width: 800
	height: 600

	Main {
		id: main

		TestCase {
			name: "View"
			when: windowShown

			function initTestCase() {
			}

			function test_main() {
				waitForRendering(root)
				wait(1000);
				var image = grabImage(main);
				image.save(docScreenshotsDir + "/View.png")
			}
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
