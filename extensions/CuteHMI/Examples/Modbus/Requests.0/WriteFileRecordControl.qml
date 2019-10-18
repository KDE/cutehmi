import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CuteHMI.Modbus 2.0

RowLayout {
	property AbstractDevice device

	Button {
		Layout.alignment: Qt.AlignTop

		text: "Write file record"
		onClicked:  {
			var subrequests = []
			for (var i = 0; i < repeater.count; i++) {
				var item = repeater.itemAt(i)
				var values = []
				for (var j = 0; j < item.valuesRepeater.count; j++)
					values.push(item.valuesRepeater.itemAt(j).value)
				subrequests.push(device.writeFileRecordSubrequest(item.file, item.address, values))
			}
			device.requestWriteFileRecord(subrequests)
		}
	}

	RowLayout {
		Layout.alignment: Qt.AlignTop

		Label {
			text: qsTr("Subrequests:")
		}

		SpinBox {
			id: subrequestsBox

			editable: true
			from: 1
			to: 10
		}
	}

	ColumnLayout {
		Repeater {
			id: repeater

			model: subrequestsBox.value

			RowLayout {
				property int file: fileBox.value
				property int address: addressBox.value
				property int amount: amountBox.value
				property var valuesRepeater: valuesRepeater

				Label {
					text: qsTr("File:")
				}

				SpinBox {
					id: fileBox

					editable: true
					from: 1
					to: 65535
				}

				Label {
					text: qsTr("Address:")
				}

				SpinBox {
					id: addressBox

					editable: true
					from: 0
					to: 0x270F
				}

				Label {
					text: qsTr("Amount:")
				}

				SpinBox {
					id: amountBox

					editable: true
					from: 1
					to: 65535
				}

				Label {
					text: qsTr("Values:")
				}

				Repeater {
					id: valuesRepeater

					model: amountBox.value

					SpinBox {
						editable: true
						from: 0
						to: 65535
					}
				}
			}
		}
	}

}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
