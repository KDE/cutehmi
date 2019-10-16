import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import CuteHMI.Modbus 2.0

GridLayout {
	columns: 2

	property TCPServer server

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Host:")
	}

	TextField {
		text: server.host
		onEditingFinished: server.host = text
	}

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Port:")
	}

	TextField {
		text: server.port
		onEditingFinished: server.port = text
	}

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Slave address:")
	}

	SpinBox {
		from: 1
		to: 247
		value: server.slaveAddress
		editable: true

		onValueChanged: server.slaveAddress = value
	}

	Label {
		Layout.alignment: Qt.AlignRight

		text: qsTr("Busy:")
	}

	Switch {
		checked: server.busy

		onCheckedChanged: server.busy = checked
	}
}
