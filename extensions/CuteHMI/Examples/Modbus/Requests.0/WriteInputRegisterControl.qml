import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CuteHMI.Modbus 2.0

RowLayout {
	property AbstractDevice device

	Button {
		text: "Write input register"
		onClicked: device.requestWriteInputRegister(addressBox.value, valueBox.value)
	}

	Label {
		text: qsTr("Address:")
	}

	SpinBox {
		id: addressBox

		editable: true
		from: 0
		to: 65535
	}

	Label {
		text: qsTr("Value:")
	}

	SpinBox {
		id: valueBox

		editable: true
		from: 0
		to: 65535
	}
}
