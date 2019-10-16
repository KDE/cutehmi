import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CuteHMI.Modbus 2.0

RowLayout {
	property AbstractDevice device

	Button {
		text: "Read FIFO queue"
		onClicked: device.requestReadFIFOQueue(addressBox.value)
	}

	Label {
		text: qsTr("FIFO pointer address:")
	}

	SpinBox {
		id: addressBox

		editable: true
		from: 0
		to: 65535
	}
}
