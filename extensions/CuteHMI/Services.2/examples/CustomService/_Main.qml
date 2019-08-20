import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Services 2.0
import Examples.CustomService 0.0

Item {
	anchors.fill: parent

	ColumnLayout {
		anchors.centerIn: parent

		GridLayout {
			columns: 2

			Text {
				Layout.alignment: Qt.AlignCenter

				text: "operation"
			}

			Text {
				Layout.alignment: Qt.AlignCenter

				text: "status"
			}

			Row {
				Layout.alignment: Qt.AlignCenter

				Button {
					text: "start"

					onClicked: service.start()
				}

				Button {
					text: "stop"

					onClicked: service.stop()
				}
			}

			Text {
				Layout.alignment: Qt.AlignCenter

				text: service.status
			}
		}

		RowLayout
		{
			Button {
				text: "unlock steering"

				onClicked: batmobile.unlockSteering()
			}

			Button {
				text: "damage"

				onClicked: batmobile.damage()
			}
		}
	}

	Service {
		id: service

		Car {
			id: batmobile
		}

		onStatusChanged: console.log("Batmobile status changed to: " + status)
	}
}
