import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import CuteHMI.Modbus 2.0

GridLayout {
	columns: 2

	property TCPClient client

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Host:")
	}

	TextField {
		text: client.host
		onEditingFinished: client.host = text
	}

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Port:")
	}

	TextField {
		text: client.port
		onEditingFinished: client.port = text
	}

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Slave address:")
	}

	SpinBox {
		from: 1
		to: 247
		value: client.slaveAddress
		editable: true

		onValueChanged: client.slaveAddress = value
	}
}
