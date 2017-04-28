import QtQuick 2.0
import QtQuick.Controls 2.1

import CuteHMI.Modbus 1.0

Item
{
	id: root

	implicitWidth: 50.0
	implicitHeight: 50.0

	property var delegate: parent
	property alias device: holdingRegisterController.device
	property alias address: holdingRegisterController.address
	property alias encoding: holdingRegisterController.encoding
	property alias valueScale: holdingRegisterController.valueScale
	property alias busy: holdingRegisterController.busy
	property alias controller: holdingRegisterController
	property alias value: holdingRegisterController.value

	property var busyIndicator: BusyIndicator {
		parent: root
		anchors.centerIn: parent
		running: holdingRegisterController.busy
	}

	HoldingRegisterController
	{
		id: holdingRegisterController
	}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
