import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CuteHMI.Modbus 2.0

RowLayout {
	property AbstractDevice device

	Button {
		text: "Write multiple input registers"

		onClicked: {
			var values = []
			for (var i = 0; i < repeater.count; i++)
				values.push(repeater.itemAt(i).value)
			device.requestWriteMultipleInputRegisters(addressBox.value, values)
		}
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
			to: device.maxWriteInputRegisters
			value: 1
		}

		Label {
			text: qsTr("Values:")
		}

		Repeater {
			id: repeater

			model: amountBox.value

			SpinBox {
				editable: true
				from: 0
				to: 65535
			}
		}
	}

}
