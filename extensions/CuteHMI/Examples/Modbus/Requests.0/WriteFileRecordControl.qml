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
