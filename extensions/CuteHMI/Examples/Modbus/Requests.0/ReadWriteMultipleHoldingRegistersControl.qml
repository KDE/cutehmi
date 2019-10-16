import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CuteHMI.Modbus 2.0

RowLayout {
	property AbstractDevice device

	Button {
		text: "Read/write multiple holding registers"
		onClicked:  {
			var values = []
			for (var i = 0; i < repeater.count; i++)
				values.push(repeater.itemAt(i).value)
			device.requestReadWriteMultipleHoldingRegisters(readAddressBox.value, readAmountBox.value, writeAddressBox.value, values)
		}
	}

	Label {
		text: qsTr("Read address:")
	}

	SpinBox {
		id: readAddressBox

		editable: true
		from: 0
		to: 65535
	}

	Label {
		text: qsTr("Read amount:")
	}

	SpinBox {
		id: readAmountBox

		editable: true
		from: 0
		to: device.maxReadHoldingRegisters
		value: 1
	}

	Label {
		text: qsTr("Write address:")
	}

	SpinBox {
		id: writeAddressBox

		editable: true
		from: 0
		to: 65535
	}

	Label {
		text: qsTr("Write amount:")
	}

	SpinBox {
		id: writeAmountBox

		editable: true
		from: 0
		to: device.maxWriteHoldingRegisters
		value: 1
	}

	Label {
		text: qsTr("Values:")
	}

	Repeater {
		id: repeater

		model: writeAmountBox.value

		SpinBox {
			editable: true
			from: 0
			to: 65535
		}
	}
}
