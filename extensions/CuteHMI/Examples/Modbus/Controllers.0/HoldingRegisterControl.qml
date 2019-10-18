import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 2.0

ColumnLayout {
	id: root

	property string title: qsTr("Holding register")

	property AbstractDevice device

	property Item delegate

	property alias controller: controller

	HoldingRegisterController {
		id: controller

		device: root.device
		address: addressBox.value
		valueScale: valueScaleBox.realValue
		encoding: encodingBox.value
		readOnWrite: readOnWriteBox.checked
		writeDelay: writeDelayBox.value
		writeMode: writeModeBox.value

		onValueUpdated: delegate.value = value
	}

	Connections {
		target: delegate
		onValueChanged: controller.value = delegate.value
	}

	Label {
		text: root.title
	}

	GroupBox {
		GridLayout {
			columns: 2

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Address:")
			}

			SpinBox {
				id: addressBox

				from: 0
				to: 65536
				editable: true
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Value scale:")
			}

			SpinBox {
				id: valueScaleBox

				from: -3
				to: 3

				property real realValue: Math.pow(10, value)

				textFromValue: function(value, locale) {
					return Number(Math.pow(10, value)).toLocaleString(locale, 'f', -from)
				}
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Encoding:")
			}

			ComboBox {
				id: encodingBox

				textRole: "key"
				model: ListModel {
					ListElement { key: "16 bit integer"; value: HoldingRegisterController.INT16 }
					ListElement { key: "16 bit unsigned integer"; value: HoldingRegisterController.UINT16 }
				}

				property int value: model.get(currentIndex).value

				onActivated: value = model.get(index).value
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Write mode:")
			}

			ComboBox {
				id: writeModeBox

				textRole: "key"
				model: ListModel {
					ListElement { key: "Delayed"; value: HoldingRegisterController.WRITE_DELAYED }
					ListElement { key: "Postponed"; value: HoldingRegisterController.WRITE_POSTPONED }
					ListElement { key: "Immediate"; value: HoldingRegisterController.WRITE_IMMEDIATE }
					ListElement { key: "Explicit"; value: HoldingRegisterController.WRITE_EXPLICIT }
				}

				property int value: model.get(currentIndex).value

				onActivated: value = model.get(index).value
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Write delay:")
			}

			SpinBox {
				id: writeDelayBox

				enabled: controller.writeMode == HoldingRegisterController.WRITE_DELAYED

				from: 0
				to: 1000
				stepSize: 100

				value: 500
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Read on write:")
			}

			CheckBox {
				id: readOnWriteBox

				checked: true
			}
		}
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
