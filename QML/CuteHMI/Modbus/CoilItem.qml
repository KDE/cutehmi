import QtQuick 2.0
import QtQuick.Controls 2.1

import CuteHMI.Modbus 1.0

/*!
  \qmltype CoilItem
  \inqmlmodule CuteHMI.Modbus
  \since CuteHMI.Modbus 1.0
  \brief Modbus coil item.

  This class is provided as a supplement to CoilController and is designed to be used with QML Designer.
  */
Item
{
	id: root

	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property var delegate: parent
	property alias device: coilController.device
	property alias address: coilController.address
	property alias busy: coilController.busy
	property alias controller: coilController

	property var busyIndicator: BusyIndicator {
		parent: root
		anchors.centerIn: parent
		running: coilController.busy
	}

	Binding
	{
		target: delegate
		property: "checked"
		value: coilController.value
	}

	CoilController
	{
		id: coilController

		value: delegate.checked
	}

	onDelegateChanged: delegate.checked = coilController.value
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
