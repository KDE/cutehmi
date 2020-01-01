import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Extras 1.4

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

Item {
	width: 800
	height: 600

	Service {
		id: serverService

		name: "TCP Server"

		TCPServer {
			id: server
			host: "127.0.0.1"
			port: 50002
			slaveAddress: 1
		}
	}

	Service {
		id: clientService

		name: "TCP Client"

		TCPClient {
			id: client
			host: "127.0.0.1"
			port: 50002
			slaveAddress: 1
		}
	}

	Row {
		anchors.verticalCenter: parent.verticalCenter
		anchors.horizontalCenter: parent.horizontalCenter

		spacing: 10

		Column {
			spacing: 10

			Button {
				text: "Client set coil"
				onClicked: client.requestWriteCoil(10, true)
			}

			Button {
				text: "Server reset coil"
				onClicked: client.requestWriteCoil(10, false)
			}

			Switch {
				id: coilSwitch

				checked: coilController.value

				onCheckedChanged: coilController.value = checked

				CoilController {
					id: coilController

					device: client
					address: 10
					onValueChanged: coilSwitch.checked = value
				}
			}

			StatusIndicator {
				active: coilController.value
			}
		}

		Column {
			spacing: 10

			Button {
				text: "Client set holding register"
				onClicked: client.requestWriteHoldingRegister(10, 2020)
			}

			Button {
				text: "Server reset holding register"
				onClicked: client.requestWriteHoldingRegister(10, 0)
			}

			SpinBox {
				id: holdingRegisterSpinBox

				from: 0
				to: 10000
				value: holdingRegisterController.value

				onValueChanged: holdingRegisterController.value = value

				HoldingRegisterController {
					id: holdingRegisterController

					device: client
					address: 10
					onValueChanged: holdingRegisterSpinBox.value = value
				}
			}

			Label {
				text: holdingRegisterController.value
			}

		}
	}

	Component.onCompleted: ServiceManager.start()
}
