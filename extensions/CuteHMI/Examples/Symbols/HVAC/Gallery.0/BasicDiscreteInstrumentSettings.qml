import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import CuteHMI.Symbols.HVAC 0.0

ElementSettings {
	element: instrument

	property BasicDiscreteInstrument instrument


	GroupBox {
		title: qsTr("Custom properties")

		Layout.fillWidth: true

		GridLayout {
			columns: 2
			Label {
				text: qsTr("Symbol:")
			}

			TextField {
				text: instrument.symbol

				onTextChanged: instrument.symbol = text
			}
		}
	}
}
