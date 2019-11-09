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

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
