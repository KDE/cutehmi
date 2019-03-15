import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI 2.0

ColumnLayout {
	anchors.fill: parent

	Column {
//		Layout.fillHeight: true
		Layout.alignment: Qt.AlignCenter

		Slider {
			id: slider

			from: 0
			to: 100
		}

		Item {
			width: 200
			height: 300

			PropItem {
				id: twoPropNumberDisplay

				anchors.horizontalCenter: parent.horizontalCenter

				leftPadding: 20
				rightPadding: 20
				bottomPadding: 40

				NumberDisplay {
					font.pixelSize: 20
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

				anchors.top: twoPropNumberDisplay.bottom
				width: parent.width
				height: parent.height - twoPropNumberDisplay.height - propNumberDisplay.height

				active: slider.value > 0
				warning: slider.value > 80
				alarm: slider.value > 90

				NumberDisplay {
					id: numberDisplay

					anchors.centerIn: parent

					font.pixelSize: 20
					value: slider.value

					warning: value > 30
					alarm: value > 70
				}
			}

			PropItem {
				id: propNumberDisplay

				anchors.top: element.bottom
				anchors.horizontalCenter: parent.horizontalCenter

				topPadding: 20

				NumberDisplay {
					font.pixelSize: 20
					value: slider.value
					fractionalWidth: 2
					unit: "Pa"

					warning: value > 60
					alarm: value > 90
				}
			}
		}
	}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: The MIT License
//(c)MP: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)MP: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)MP: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
