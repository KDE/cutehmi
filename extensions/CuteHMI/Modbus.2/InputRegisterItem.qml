import QtQuick 2.0
import QtQuick.Controls 2.1

import CuteHMI.Modbus 2.0

import "RegisterItem.js" as Private

Item
{
	id: root

	implicitWidth: 50.0
	implicitHeight: 50.0

	property var delegate: parent
	property string delegateProperty: "value"
	property bool readOnly: true

	property alias device: controller.device
	property alias address: controller.address
	property alias encoding: controller.encoding
	property alias valueScale: controller.valueScale
	property alias busy: controller.busy
	property alias readOnWrite: controller.readOnWrite
	property alias writeMode: controller.writeMode
	property alias writeDelay: controller.writeDelay
	property alias controller: controller

	property var busyIndicator: BusyIndicator {
		parent: root
		anchors.centerIn: parent
		running: controller.busy
	}

	InputRegisterController
	{
		id: controller
	}

	// Private properties.
	QtObject
	{
		id: p

		property var delegateValue: delegate[delegateProperty]
	}

	Component.onCompleted: Private.onCompleted()

	Component.onDestruction: Private.onDestruction()

	onReadOnlyChanged: Private.onReadOnlyChanged()
}

//(c)C: Copyright © , . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
