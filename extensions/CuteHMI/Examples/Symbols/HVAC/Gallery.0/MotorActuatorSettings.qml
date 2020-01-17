import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import CuteHMI.Symbols.HVAC 0.0

ElementSettings {
	element: actuator

	property MotorActuator actuator


	GroupBox {
		title: qsTr("Custom properties")

		Layout.fillWidth: true

		GridLayout {
			columns: 2

			Label {
				text: qsTr("Symbol:")
			}

			TextField {
				text: actuator.symbol

				onTextChanged: actuator.symbol = text
			}

			Label {
				text: qsTr("Start angle:")
			}

			Slider {
				from: 0
				to: 100

				value: actuator.start * 100

				onValueChanged: actuator.start = value / 100
			}

			Label {
				text: qsTr("Value:")
			}

			Slider {
				from: 0
				to: 100

				value: actuator.value * 100

				onValueChanged: actuator.value = value / 100
			}
		}
	}
}
