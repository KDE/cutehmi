import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Extras 1.4

//! [Import statements]
import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0
//! [Import statements]

/**
  %View component.
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
				onClicked: server.requestWriteCoil(10, false)
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
				onClicked: server.requestWriteHoldingRegister(10, 0)
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
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
