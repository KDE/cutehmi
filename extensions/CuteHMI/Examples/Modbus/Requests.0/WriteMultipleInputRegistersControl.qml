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

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
