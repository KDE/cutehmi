import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQml.Models 2.1

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

GridLayoutModel {
	id: root

	property HoldingRegisterController controller
	property alias text: label.text

	Label {
		id: label

		Layout.alignment: Qt.AlignCenter

		text: qsTr("Holding register")
	}

	SpinBox {
		id: addressSpinBox

		Layout.alignment: Qt.AlignCenter

		value: controller.address
		editable: true

		onValueChanged: controller.address = value
	}

	SpinBox {
		id: valueSpinBox

		value:  controller.value

		onValueChanged: controller.value = value

		BusyIndicator {
			anchors.centerIn: parent

			running: controller.busy
		}
	}
}
