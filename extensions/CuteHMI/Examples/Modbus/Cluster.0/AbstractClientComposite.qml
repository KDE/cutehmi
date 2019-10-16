import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 2.0

RowLayout {
	spacing: 20

	property AbstractClient client

	property alias settings: settingsBoxLayout.children

	ColumnLayout {
		GridLayout {
			columns: 2

			Label {
				text: qsTr("State:")
			}

			Label {
				text: {
					switch (client.state) {
						case AbstractClient.CONNECTING:
							return qsTr("Connecting")
						case AbstractClient.CONNECTED:
							return qsTr("Connected")
						case AbstractClient.DISCONNECTING:
							return qsTr("Disconnecting")
						case AbstractClient.DISCONNECTED:
							return qsTr("Disconnected")
						default:
							return qsTr("Unrecognized state")
					}
				}
			}
		}

		GroupBox {
			id: settingsBox

			RowLayout {
				id: settingsBoxLayout
			}
		}

		Row {
			Layout.alignment: Qt.AlignRight

			spacing: 5

			Button {
				text: qsTr("Connect")
				onClicked: client.connect()
			}

			Button {
				text: qsTr("Disconnect")
				onClicked: client.disconnect()
			}
		}
	}

	DeviceControls {
		device: client
	}
}
