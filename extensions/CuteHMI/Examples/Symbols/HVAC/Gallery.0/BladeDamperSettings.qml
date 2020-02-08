import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import CuteHMI.Symbols.HVAC 0.0

ElementSettings {
	element: damper

	property BladeDamper damper

	GroupBox {
		title: qsTr("Custom properties")

		Layout.fillWidth: true

		GridLayout {
			columns: 2

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Mirror:")
			}

			CheckBox {
				checked: damper.mirror

				onCheckedChanged: damper.mirror = checked
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Blades:")
			}

			SpinBox {
				from: 1
				to: 10
				value:  damper.blades

				onValueChanged: damper.blades = value
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Value:")
			}

			Slider {
				id: valueSlider

				from: 0
				to: 100

				value: damper.value * 100

				onValueChanged: damper.value = value / 100
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Opposed blade:")
			}

			CheckBox {
				checked: damper.opposedBlade

				onCheckedChanged: damper.opposedBlade = checked
			}
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
