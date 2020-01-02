import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Extras 1.4

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

/**
  %Main component.
*/
Item {
	width: 800
	height: 600

	//! [Setting up server service]
	Service {
		id: serverService

		name: "TCP Server"

		//! [Configuring a server]
		TCPServer {
			id: server

			host: "127.0.0.1"
			port: 50002
			slaveAddress: 1
		}
		//! [Configuring a server]
	}
	//! [Setting up server service]

	//! [Setting up client service]
	Service {
		id: clientService

		name: "TCP Client"

		//! [Configuring a client]
		TCPClient {
			id: client

			host: "127.0.0.1"
			port: 50002
			slaveAddress: 1
		}
		//! [Configuring a client]
	}
	//! [Setting up client service]

	Row {
		anchors.verticalCenter: parent.verticalCenter
		anchors.horizontalCenter: parent.horizontalCenter

		spacing: 10

		Column {
			spacing: 10

			//! [Client set coil button]
			Button {
				text: "Client set coil"
				onClicked: client.requestWriteCoil(10, true)
			}
			//! [Client set coil button]

			//! [Server reset coil button]
			Button {
				text: "Server reset coil"
				onClicked: client.requestWriteCoil(10, false)
			}
			//! [Server reset coil button]

			Switch {
				id: coilSwitch

				checked: coilController.value

				//! [Switch onCheckedChanged handler]
				onCheckedChanged: coilController.value = checked
				//! [Switch onCheckedChanged handler]

				//! [Coil controller]
				CoilController {
					id: coilController

					device: client
					address: 10
					onValueChanged: coilSwitch.checked = value
				}
				//! [Coil controller]
			}

			StatusIndicator {
				//! [Status indicator binding]
				active: coilController.value
				//! [Status indicator binding]
			}
		}

		Column {
			spacing: 10

			//! [Holding register controls]
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
			//! [Holding register controls]
		}
	}

	//! [Start services]
	Component.onCompleted: ServiceManager.start()
	//! [Start services]
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
