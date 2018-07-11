import QtQuick 2.0
import QtQuick.Controls 2.1

import CuteHMI.Modbus 1.0

Item
{
	id: root

	implicitWidth: 50.0
	implicitHeight: 50.0

	property var delegate: parent
	property string delegateProperty: "checked"

	property alias device: discreteInputController.device
	property alias address: discreteInputController.address
	property alias busy: discreteInputController.busy
	property alias controller: discreteInputController

	property var busyIndicator: BusyIndicator {
		parent: root
		anchors.centerIn: parent
		running: discreteInputController.busy
	}

	DiscreteInputController {
		id: discreteInputController

		onValueUpdated: delegate[delegateProperty] = value
	}

	Component.onCompleted: delegate[delegateProperty] = controller.value
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
