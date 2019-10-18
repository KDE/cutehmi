import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQml.Models 2.1

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

GridLayoutModel {
	id: root

	property InputRegisterController controller
	property alias text: label.text

	Label {
		id: label

		Layout.alignment: Qt.AlignCenter

		text: qsTr("Input register")
	}

	SpinBox {
		id: addressSpinBox

		Layout.alignment: Qt.AlignCenter

		value: controller.address
		editable: true

		onValueChanged: controller.address = value
	}

	SpinBox {
		id: valueSpinBox

		value:  controller.value

		onValueChanged: controller.value = value

		BusyIndicator {
			anchors.centerIn: parent

			running: controller.busy
		}
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
