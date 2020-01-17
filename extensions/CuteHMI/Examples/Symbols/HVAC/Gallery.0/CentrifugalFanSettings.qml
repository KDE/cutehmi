import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import CuteHMI.Symbols.HVAC 0.0

ElementSettings {
	element: fan

	property CentrifugalFan fan


	GroupBox {
		title: qsTr("Custom properties")

		Layout.fillWidth: true

		GridLayout {
			columns: 2

			Label {
				text: qsTr("Mirror:")
			}

			CheckBox {
				checked: fan.mirror

				onCheckedChanged: fan.mirror = checked
			}

			Label {
				text: qsTr("RPM:")
			}

			Slider {
				from: 0
				to: 120

				value: fan.implicitRpm

				onValueChanged: fan.implicitRpm = value
			}
		}
	}
}
