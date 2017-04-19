import QtQuick 2.0
import QtQuick.Controls 2.1

import CuteHMI.Modbus 1.0

Item
{
	id: root

	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property var delegate: parent
	property alias device: inputRegisterController.device
	property alias address: inputRegisterController.address
	property alias encoding: inputRegisterController.encoding
	property alias valueScale: inputRegisterController.valueScale
	property alias busy: inputRegisterController.busy
	property alias controller: inputRegisterController

	property var busyIndicator: BusyIndicator {
		parent: root
		anchors.centerIn: parent
		running: inputRegisterController.busy
	}

	Binding
	{
		target: delegate
		property: "value"
		value: inputRegisterController.value
	}

	InputRegisterController
	{
		id: inputRegisterController
	}

	onDelegateChanged: delegate.value = inputRegisterController.value
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
