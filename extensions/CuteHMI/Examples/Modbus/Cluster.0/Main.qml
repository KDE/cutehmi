import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQml.Models 2.11

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

Item {

	Component {
		id: clientLoaderComponent

		DeviceLoader {
		}
	}

	ObjectModel {
		id: clientModel

		DeviceLoader {
		}
	}

	ColumnLayout
	{
		anchors.fill: parent
		anchors.margins: 20

		ListView {
			Layout.fillWidth: true
			Layout.fillHeight: true

			clip: true

			model: clientModel
		}

		Row {
			spacing: 5

			Button {
				text: qsTr("Add")

				onClicked: clientModel.append(clientLoaderComponent.createObject())
			}

			Button {
				text: qsTr("Remove")

				onClicked: if (clientModel.count) clientModel.remove(clientModel.count - 1)
			}
		}
	}


//	ColumnLayout {
//		anchors.centerIn: parent
//		spacing: 20

//		Label {
//			text: qsTr("Client")
//			font.bold: true
//		}

//		RowLayout {
//			spacing: 20

//			DummyClientSettings {
//				client: DummyClient {}
//			}

////			GridLayout {
////				rows: 4
////				flow: GridLayout.TopToBottom

////				Label {
////					Layout.alignment: Qt.AlignRight

////					text: qsTr("Register type:")
////				}

////				Label {
////					Layout.alignment: Qt.AlignRight

////					text: qsTr("Address:")
////				}

////				Label {
////					Layout.alignment: Qt.AlignRight

////					text: qsTr("Value:")
////				}

////				Label {
////					Layout.alignment: Qt.AlignRight

////					text: qsTr("Operation:")
////				}

////				Label {
////					Layout.alignment: Qt.AlignCenter

////					text: qsTr("Coil")
////				}

////				SpinBox {
////					id: coilAddress

////					Layout.alignment: Qt.AlignCenter

////					value: 0
////					editable: true
////				}

////				Switch {
////					id: coilValue

////					Layout.alignment: Qt.AlignCenter

////					checked: false
////				}

////				Row {
////					Layout.alignment: Qt.AlignCenter

////					spacing: 5

////					Button {
////						text: qsTr("Write")
////						onClicked: console.log("Write coil request " + client.requestWriteCoil(coilAddress.value, coilValue.checked) + ".")
////					}

////					Button {
////						text: qsTr("Read")
////						onClicked: console.log("Read coil request " + client.requestReadCoil(coilAddress.value) + ".")
////					}

////					Button {
////						text: qsTr("Temp (raw)")
////						onClicked: {
////							console.log("Sending raw request.")
////							client.request(TCPClient.READ_COILS, {"address": 0, "numberOfCoils": 6})
////						}
////					}
////				}
////			}
//		}
//	}
}
