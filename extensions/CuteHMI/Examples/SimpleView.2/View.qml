import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.GUI 1.0

ColumnLayout {
	anchors.fill: parent

	property real quadrat: Theme.units.quadrat

	Column {
		Layout.alignment: Qt.AlignCenter

		Slider {
			id: slider

			from: 0
			to: 100
		}

		Item {
			width: quadrat * 2.5
			height: quadrat * 3.75

			PropItem {
				id: sidePropNumberDisplay

				anchors.horizontalCenter: parent.horizontalCenter

				leftPadding: quadrat * 0.25
				rightPadding: quadrat * 0.25
				bottomPadding: quadrat * 0.5

				NumberDisplay {
					value: slider.value * 10
					integralWidth: 4
					fractionalWidth: 0
					unit: "kWh"

					warning: value > 500
					alarm: value > 800
				}
			}

			RectangularElement {
				id: element

				anchors.top: sidePropNumberDisplay.bottom
				width: parent.width
				height: parent.height - sidePropNumberDisplay.height - propNumberDisplay.height

				active: slider.value > 0
				warning: slider.value > 80
				alarm: slider.value > 90

				NumberDisplay {
					id: numberDisplay

					anchors.centerIn: parent

					value: slider.value

					warning: value > 30
					alarm: value > 70
				}
			}

			PropItem {
				id: propNumberDisplay

				anchors.top: element.bottom
				anchors.horizontalCenter: parent.horizontalCenter

				topPadding: quadrat * 0.25

				NumberDisplay {
					value: slider.value
					fractionalWidth: 2
					unit: "Pa"

					warning: value > 60
					alarm: value > 90
				}
			}
		}
	}

	Component.onCompleted: {
		Theme.units.quadrat = 80
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
