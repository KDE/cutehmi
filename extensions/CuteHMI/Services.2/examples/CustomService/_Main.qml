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

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
