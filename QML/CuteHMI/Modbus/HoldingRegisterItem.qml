import QtQuick 2.0
import QtQuick.Controls 2.1

import CuteHMI.Modbus 1.0

Item
{
	id: root

	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property var delegate: parent
	property alias device: holdingRegisterController.device
	property alias address: holdingRegisterController.address
	property alias encoding: holdingRegisterController.encoding
	property alias valueScale: holdingRegisterController.valueScale
	property alias busy: holdingRegisterController.busy
	property alias controller: holdingRegisterController

	property var busyIndicator: BusyIndicator {
		parent: root
		anchors.centerIn: parent
		running: holdingRegisterController.busy
	}

	Binding
	{
		target: delegate
		property: "value"
		value: holdingRegisterController.value
	}

	HoldingRegisterController
	{
		id: holdingRegisterController

		value: delegate.value
	}

	onDelegateChanged: delegate.value = holdingRegisterController.value
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
