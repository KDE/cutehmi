import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CuteHMI.Modbus 2.0

RowLayout {
	property AbstractDevice device

	property int andMask: 0
	property int orMask: 0

	Button {
		text: "Mask write 4X register"
		onClicked: device.requestMaskWriteHoldingRegister(addressBox.value, parent.andMask, parent.orMask)
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
		text: qsTr("And mask (hex):")
	}

	TextField {
		text: "0x" + parent.andMask.toString(16)
		validator: RegExpValidator {
			regExp: /0x[0-9A-Fa-f]{1,4}/
		}

		onAccepted: parent.andMask = parseInt(text)
	}

	Label {
		text: qsTr("Or mask (hex):")
	}

	TextField {
		text: "0x" + parent.orMask.toString(16)
		validator: RegExpValidator {
			regExp: /0x[0-9A-Fa-f]{1,4}/
		}

		onAccepted: parent.orMask = parseInt(text)
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
