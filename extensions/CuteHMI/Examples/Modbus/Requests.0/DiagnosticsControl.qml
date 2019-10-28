import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CuteHMI.Modbus 2.0

RowLayout {
	property AbstractDevice device

	property int diagnosticsData

	Button {
		text: "Diagnostics"
		onClicked: device.requestDiagnostics(subfunctionBox.value, parent.diagnosticsData)
	}

	Label {
		text: qsTr("Subfunction:")
	}

	ComboBox {
		id: subfunctionBox

		implicitWidth: 250
		textRole: "key"
		model: ListModel {
			ListElement { key: qsTr("Return query data"); value: AbstractDevice.DIAGNOSTICS_RETURN_QUERY_DATA }
			ListElement { key: qsTr("Restart communications option"); value: AbstractDevice.DIAGNOSTICS_RESTART_COMM_OPTION }
			ListElement { key: qsTr("Return diagnostics register"); value: AbstractDevice.DIAGNOSTICS_RETURN_DIAGNOSTICS_REGISTER }
			ListElement { key: qsTr("Change ASCII input delimeter"); value: AbstractDevice.DIAGNOSTICS_CHANGE_ASCII_INPUT_DELIMITER }
			ListElement { key: qsTr("Force listen only mode"); value: AbstractDevice.DIAGNOSTICS_FORCE_LISTEN_ONLY_MODE }
			ListElement { key: qsTr("Clear counters and diagnostic register"); value: AbstractDevice.DIAGNOSTICS_CLEAR_COUNTERS_AND_DIAGNOSTICS_REGISTER }
			ListElement { key: qsTr("Return bus message count"); value: AbstractDevice.DIAGNOSTICS_RETURN_BUS_MESSAGE_COUNT }
			ListElement { key: qsTr("Return bus communication error count"); value: AbstractDevice.DIAGNOSTICS_RETURN_BUS_COMM_ERROR_COUNT }
			ListElement { key: qsTr("Return bus exception error count"); value: AbstractDevice.DIAGNOSTICS_RETURN_BUS_EXCEPTION_ERROR_COUNT }
			ListElement { key: qsTr("Return slave message count"); value: AbstractDevice.DIAGNOSTICS_RETURN_SLAVE_MESSAGE_COUNT }
			ListElement { key: qsTr("Return slave no response count"); value: AbstractDevice.DIAGNOSTICS_RETURN_SLAVE_NO_RESPONSE_COUNT }
			ListElement { key: qsTr("Return slave NAK count"); value: AbstractDevice.DIAGNOSTICS_RETURN_SLAVE_NAK_COUNT }
			ListElement { key: qsTr("Return slave busy count"); value: AbstractDevice.DIAGNOSTICS_RETURN_SLAVE_BUSY_COUNT }
			ListElement { key: qsTr("Return bus character overrun count"); value: AbstractDevice.DIAGNOSTICS_RETURN_BUS_CHARACTER_OVERRUN_COUNT }
			ListElement { key: qsTr("Return IOP overrun count"); value: AbstractDevice.DIAGNOSTICS_RETURN_IOP_OVERRUN_COUNT }
			ListElement { key: qsTr("Clear overrun counter and flag"); value: AbstractDevice.DIAGNOSTICS_CLEAR_OVERRUN_COUNTER_AND_FLAG }
			ListElement { key: qsTr("Get/Clear modbus plus statistics"); value: AbstractDevice.DIAGNOSTICS_GET_CLEAR_MODBUS_PLUS_STATISTICS }
		}

		property int value: model.get(currentIndex).value

		onActivated: value = model.get(index).value
	}

	Label {
		text: qsTr("Data:")
	}

	TextField {
		text: parent.diagnosticsData
		validator: IntValidator {
			bottom: 0
			top: 65535
		}

		onAccepted: parent.diagnosticsData = Number.fromLocaleString(locale, text)
	}

	Label {
		text: qsTr("Data (hex):")
	}

	TextField {
		text: "0x" + parent.diagnosticsData.toString(16)
		validator: RegExpValidator {
			regExp: /0x[0-9A-Fa-f]{1,4}/
		}

		onAccepted: parent.diagnosticsData = parseInt(text)
	}
}

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
