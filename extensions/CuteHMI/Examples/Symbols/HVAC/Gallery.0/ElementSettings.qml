import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import CuteHMI.GUI 0.0

ColumnLayout {
	Layout.fillWidth: true

	property Element element

	GroupBox {
		Layout.fillWidth: true

		title: qsTr("Common properties")

		ColumnLayout {
			CheckBox {
				text: qsTr("Neutral colors")

				onCheckedChanged: checked ? element.colorSet = CuteApplication.theme.palette.neutral : element.colorSet = Qt.binding(element.currentStateColorSet)
			}

			CheckBox {
				text: qsTr("Active")

				checked: element.active

				onCheckedChanged: element.active = checked
			}

			CheckBox {
				text: qsTr("Warning")

				checked: element.warning

				onCheckedChanged: element.warning = checked
			}

			CheckBox {
				text: qsTr("Alarm")

				checked: element.alarm

				onCheckedChanged: element.alarm = checked
			}
		}
	}
}
