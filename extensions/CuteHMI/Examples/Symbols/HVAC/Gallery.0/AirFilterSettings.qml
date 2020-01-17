import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import CuteHMI.Symbols.HVAC 0.0

ElementSettings {
	element: filter

	property AirFilter filter

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
				checked: filter.mirror

				onCheckedChanged: filter.mirror = checked
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Pockets:")
			}

			SpinBox {
				from: 1
				to: 10
				value:  filter.pockets

				onValueChanged: filter.pockets = value
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Fill:")
			}

			Slider {
				id: fillSlider

				from: 0
				to: 100

				onValueChanged: filter.fill = value / 100
			}
		}
	}
}
