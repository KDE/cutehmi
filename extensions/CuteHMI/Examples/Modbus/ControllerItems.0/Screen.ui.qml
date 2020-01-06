import QtQuick 2.0
import QtQuick.Controls 2.0

import CuteHMI.Modbus 2.0

Item {
	Switch {
		id: element
		x: 10
		y: 10
		text: qsTr("Switch")

		CoilItem {
			id: coilItem
			device: client
			address: 10
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
		}
	}

	CheckBox {
		id: checkBox
		x: 10
		y: 80
		text: qsTr("Check Box")

		CoilItem {
			id: coilItem1
			device: client
			address: 10
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
		}
	}

	Label {
		id: label
		x: 227
		y: 94
		text: qsTr("Label")

		HoldingRegisterItem {
			id: holdingRegisterItem1
			device: client
			delegateProperty: "text"
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
			address: 10
		}
	}

	SpinBox {
		id: spinBox
		x: 160
		y: 10

		HoldingRegisterItem {
			id: holdingRegisterItem
			device: client
			address: 10
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.verticalCenter: parent.verticalCenter
		}
	}
}

/*##^##
Designer {
	D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

