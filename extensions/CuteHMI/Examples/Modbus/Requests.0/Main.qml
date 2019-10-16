import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 2.0
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
