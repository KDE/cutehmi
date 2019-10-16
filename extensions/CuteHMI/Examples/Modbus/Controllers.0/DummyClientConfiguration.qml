import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 2.0

GridLayout {
	columns: 2

	property DummyClient client

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
