import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 2.0

AbstractClientComposite {
	client: DummyClient {}
//	settings: Rectangle {
//		width: 200
//		height: 200
//		color: "red"
//	}

//	settings: RowLayout {
//		width: 200
//		height: 200

//		Rectangle {
//			Layout.fillHeight: true
//			Layout.fillWidth: true
//			color: "red"
//		}
//	}


//	RowLayout {
//		parent: settingsBox
//		width: 200
//		height: 200

//		Rectangle {
//			Layout.fillHeight: true
//			Layout.fillWidth: true
//			color: "red"
//		}
//	}
	settings: GridLayout {
		columns: 2

		Label {
			Layout.alignment: Qt.AlignRight

			text: qsTr("Connect latency:")
		}

		SpinBox {
			from: 0
			to: 10
			value: client.connectLatency / 1000
			editable: true

			onValueChanged: client.connectLatency = value * 1000
		}

		Label {
			Layout.alignment: Qt.AlignRight

			text: qsTr("Disconnect latency:")
		}

		SpinBox {
			from: 0
			to: 10
			value: client.disconnectLatency / 1000
			editable: true

			onValueChanged: client.disconnectLatency = value * 1000
		}

		Label {
			Layout.alignment: Qt.AlignRight

			text: qsTr("Latency (requests):")
		}

		SpinBox {
			from: 0
			to: 10
			value: client.latency / 1000
			editable: true

			onValueChanged: client.latency = value * 1000
		}

	}
}

//RowLayout {
//	DummyClient {
//		id: client
//	}

//	GridLayout {
//		columns: 2

//		Label {
//			Layout.alignment: Qt.AlignRight

//			text: qsTr("State:")
//		}

//		Label {
//			text: {
//				switch (client.state) {
//					case DummyClient.CONNECTING:
//						return qsTr("Connecting")
//					case DummyClient.CONNECTED:
//						return qsTr("Connected")
//					case DummyClient.DISCONNECTING:
//						return qsTr("Disconnecting")
//					case DummyClient.DISCONNECTED:
//						return qsTr("Disconnected")
//					default:
//						return qsTr("Unrecognized state")
//				}
//			}
//		}

//		Label {
//			Layout.alignment: Qt.AlignRight

//			text: qsTr("Connect latency:")
//		}

//		SpinBox {
//			from: 0
//			to: 10
//			value: client.openLatency / 1000
//			editable: true

//			onValueChanged: client.openLatency = value * 1000
//		}

//		Label {
//			Layout.alignment: Qt.AlignRight

//			text: qsTr("Disconnect latency:")
//		}

//		SpinBox {
//			from: 0
//			to: 10
//			value: client.closeLatency / 1000
//			editable: true

//			onValueChanged: client.closeLatency = value * 1000
//		}

//		Label {
//			Layout.alignment: Qt.AlignRight

//			text: qsTr("Latency:")
//		}

//		SpinBox {
//			from: 0
//			to: 10
//			value: client.latency / 1000
//			editable: true

//			onValueChanged: client.latency = value * 1000
//		}

//		Row {
//			Layout.columnSpan: 2
//			Layout.alignment: Qt.AlignRight

//			spacing: 5

//			Button {
//				text: qsTr("Connect")
//				onClicked: client.connect()
//			}

//			Button {
//				text: qsTr("Disconnect")
//				onClicked: client.disconnect()
//			}
//		}
//	}

//	DeviceControls {
//		device: client
//	}
//}
