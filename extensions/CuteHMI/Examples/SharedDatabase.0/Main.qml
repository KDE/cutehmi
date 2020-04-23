import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Services 2.0
import CuteHMI.SharedDatabase 0.0

ColumnLayout {
	anchors.fill: parent

	Service {
		id: service

		name: "Database Service"

		Database {
			connectionName: "exampleConnection"
			type: "QSQLITE"
			host: "localhost"
			port: 5432
			name: "test"
			user: "bill"
			password: "windows"
		}
	}

	ColumnLayout {
		Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

		Row {
			spacing: 5

			Label {
				text: service.name + ":"
			}

			Label {
				text: service.status
			}
		}

		Row {
			spacing: 5

			Button {
				text: qsTr("Start")
				onClicked: service.start()
			}

			Button {
				text: qsTr("Stop")
				onClicked: service.stop()
			}
		}
	}
}

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
