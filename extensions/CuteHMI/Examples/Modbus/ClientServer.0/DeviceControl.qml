import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

ColumnLayout {
	id: root

	property AbstractDevice device
	property Item configurationItem

	RowLayout {
		Label {
			text: qsTr("Device state:")
		}

		Label {
			text: {
				switch (device.state) {
					case AbstractDevice.OPENING:
						return qsTr("Opening")
					case AbstractDevice.OPENED:
						return qsTr("Opened")
					case AbstractDevice.CLOSING:
						return qsTr("Closing")
					case AbstractDevice.CLOSED:
						return qsTr("Closed")
					default:
						return qsTr("Unrecognized state")
				}
			}
		}
	}

	GroupBox {
		contentItem: configurationItem
	}

	Row {
		Layout.alignment: Qt.AlignRight

		spacing: 5

		Button {
			text: qsTr("Open")
			onClicked: device.open()
		}

		Button {
			text: qsTr("Close")
			onClicked: device.close()
		}
	}
}
