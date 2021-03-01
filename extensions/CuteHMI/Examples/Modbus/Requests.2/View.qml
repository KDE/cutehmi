import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 3.0
import CuteHMI.Services 2.0

Item {
	anchors.fill: parent

	TCPServer {
		id: server
	}

	TCPClient {
		id: client
	}

	RowLayout {
		anchors.fill: parent
		anchors.margins: 40
		spacing: 40


		ColumnLayout {
			spacing: 40

			DeviceControl {
				text: qsTr("Server state:")
				device: server
				configurationItem: TCPServerConfiguration {
					server: server
				}
			}

			DeviceControl {
				text: qsTr("Client state:")
				device: client
				configurationItem: TCPClientConfiguration {
					client: client
				}
			}
		}

		ColumnLayout {
			Layout.fillHeight: true
			Layout.fillWidth: true

			ComboBox {
				id: deviceBox

				model: ["Server", "Client"]
				currentIndex: 1

				property AbstractDevice device: client

				onActivated: {
					if (currentText === "Server")
						device = server
					else if (currentText === "Client")
						device = client
				}

				onDeviceChanged: {
					device.requestCompleted.disconnect(deviceRquestReplyArea.onRequestCompleted)
					device.requestCompleted.connect(deviceRquestReplyArea.onRequestCompleted)
				}
			}

			Flickable {
				Layout.fillHeight: true
				Layout.fillWidth: true

				ScrollBar.vertical: ScrollBar {}
				ScrollBar.horizontal: ScrollBar {}

				clip: true
				contentWidth: requestsLayout.implicitWidth
				contentHeight: requestsLayout.implicitHeight

				ColumnLayout {
					id: requestsLayout

					ReadCoilsControl {
						device: deviceBox.device
					}

					WriteCoilControl {
						device: deviceBox.device
					}

					WriteMultipleCoilsControl {
						device: deviceBox.device
					}

					ReadDiscreteInputsControl {
						device: deviceBox.device
					}

					WriteDiscreteInputControl {
						device: deviceBox.device
					}

					WriteMultipleDiscreteInputsControl {
						device: deviceBox.device
					}

					ReadHoldingRegistersControl {
						device: deviceBox.device
					}

					WriteHoldingRegisterControl {
						device: deviceBox.device
					}

					WriteMultipleHoldingRegistersControl {
						device: deviceBox.device
					}

					ReadInputRegistersControl {
						device: deviceBox.device
					}

					WriteInputRegisterControl {
						device: deviceBox.device
					}

					WriteMultipleInputRegistersControl {
						device: deviceBox.device
					}

					ReadExceptionStatusControl {
						device: deviceBox.device
					}

					DiagnosticsControl {
						device: deviceBox.device
					}

					ReportSlaveIdControl {
						device: deviceBox.device
					}

					FetchCommEventCounterControl {
						device: deviceBox.device
					}

					FetchCommEventLogControl {
						device: deviceBox.device
					}

					ReadFIFOQueueControl {
						device: deviceBox.device
					}

					MaskWrite4xRegisterControl {
						device: deviceBox.device
					}

					ReadWriteMultipleHoldingRegistersControl {
						device: deviceBox.device
					}

					ReadFileRecordControl {
						device: deviceBox.device
					}

					WriteFileRecordControl {
						device: deviceBox.device
					}
				}
			}

			TextArea {
				id: deviceRquestReplyArea

				readOnly: true

				function onRequestCompleted(request, reply) {
					text = "Request: " + JSON.stringify(request) + "\nReply: " + JSON.stringify(reply)
				}
			}

		}
	}
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
