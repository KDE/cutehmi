import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CuteHMI.Modbus 2.0

RowLayout {
	property AbstractDevice device

	Button {
		text: "Read input registers"
		onClicked: device.requestReadInputRegisters(addressBox.value, amountBox.value)
	}

	RowLayout {
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
			text: qsTr("Amount:")
		}

		SpinBox {
			id: amountBox

			editable: true
			from: 0
			to: device.maxReadInputRegisters
			value: 1
		}
	}
}
