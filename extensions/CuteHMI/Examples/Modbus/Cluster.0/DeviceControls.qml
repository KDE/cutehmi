import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 2.0

GridLayout {
	id: root

	rows: 4
	flow: GridLayout.TopToBottom

	property AbstractDevice device

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Register type:")
	}

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Address:")
	}

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Value:")
	}

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Operation:")
	}

	Label {
		Layout.alignment: Qt.AlignCenter

		text: qsTr("Coil")
	}

	SpinBox {
		id: coilAddress

		Layout.alignment: Qt.AlignCenter

		value: 0
		editable: true
	}

	Switch {
		id: coilSwitch

		Layout.alignment: Qt.AlignCenter

		checked: false

		onCheckedChanged: {
			console.log("checked: ", checked)
			coilController.value = checked
			console.log("coilController.value: ", coilController.value)
		}

		CoilController {
			id: coilController

			device: root.device
			address: coilAddress.value

			onValueChanged: coilSwitch.checked = value
		}
	}

	Row {
		Layout.alignment: Qt.AlignCenter

		spacing: 5

		Button {
			text: qsTr("Write")
			onClicked: {
				console.log("Write coil request...")
				device.requestWriteCoil(coilAddress.value, coilSwitch.checked)
			}
		}

		Button {
			text: qsTr("Read")
			onClicked: {
				console.log("Read coil request...")
				device.requestReadCoils(coilAddress.value)
			}
		}

		Button {
			text: qsTr("Temp (raw)")
			onClicked: {
				console.log("Sending raw request...")
				device.request(AbstractDevice.REQUEST_READ_COILS, {"startAddress": 0, "amount": 6})
			}
		}
	}


	Label {
		Layout.alignment: Qt.AlignCenter

		text: qsTr("Holding register")
	}

	SpinBox {
		id: hrAddress

		Layout.alignment: Qt.AlignCenter

		value: 0
		editable: true
	}

	SpinBox {
		id: hrSpinBox

		Layout.alignment: Qt.AlignCenter

		from: 0
		to: 1000

		onValueChanged: {
			console.log("value changed: ", value)
			hrController.value = value
			console.log("hrController.value: ", hrController.value)
		}

		HoldingRegisterController {
			id: hrController

			device: root.device
			address: hrAddress.value

			onValueChanged: hrSpinBox.value = value
		}
	}

	Row {
		Layout.alignment: Qt.AlignCenter

		spacing: 5

		Button {
			text: qsTr("Write")
			onClicked: {
				console.log("Write holding register request...")
				device.requestWriteHoldingRegister(hrAddress.value, hrSpinBox.value)
			}
		}

		Button {
			text: qsTr("Read")
			onClicked: {
				console.log("Read holding register request...")
				device.requestReadHoldingRegisters(hrAddress.value)
			}
		}

		Button {
			text: qsTr("Temp (raw)")
			onClicked: {
				console.log("Sending raw request...")
				device.request(AbstractDevice.REQUEST_READ_HOLDING_REGISTERS, {"address": 0, "amount": 6})
			}
		}
	}
}
