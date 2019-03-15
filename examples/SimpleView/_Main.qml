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
//(c)MP: This Source Code Form is subject to the terms of the DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE, Version 1.
//(c)MP: DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//(c)MP: 0. You just DO WHAT THE FUCK YOU WANT TO.
//(c)MP: 1. NO FUCKING WARRANTY!
