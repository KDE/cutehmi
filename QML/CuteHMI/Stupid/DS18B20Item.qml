import QtQuick 2.0
import QtQuick.Controls 1.3

import CuteHMI.Stupid 1.0

Item
{
	id: root

	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property alias busyIndicator: busyIndicator
	property alias controller: controller

	BusyIndicator
	{
		id: busyIndicator

		anchors.centerIn: parent
		running: controller.busy
	}

	DS18B20Controller
	{
		id: controller
	}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
