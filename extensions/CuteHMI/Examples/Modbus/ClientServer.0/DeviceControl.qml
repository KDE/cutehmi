import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

ColumnLayout {
	id: root

	property AbstractDevice device
	property Item configurationItem

	RowLayout {
		Label {
			text: qsTr("Device state:")
		}

		Label {
			text: {
				switch (device.state) {
					case AbstractDevice.OPENING:
						return qsTr("Opening")
					case AbstractDevice.OPENED:
						return qsTr("Opened")
					case AbstractDevice.CLOSING:
						return qsTr("Closing")
					case AbstractDevice.CLOSED:
						return qsTr("Closed")
					default:
						return qsTr("Unrecognized state")
				}
			}
		}
	}

	GroupBox {
		contentItem: configurationItem
	}

	Row {
		Layout.alignment: Qt.AlignRight

		spacing: 5

		Button {
			text: qsTr("Open")
			onClicked: device.open()
		}

		Button {
			text: qsTr("Close")
			onClicked: device.close()
		}
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
