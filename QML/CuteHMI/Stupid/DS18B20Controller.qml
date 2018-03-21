import QtQuick 2.0

import CuteHMI.Stupid 1.0

import "DS18B20Controller.js" as Private

QtObject
{
	id: root

	property var device
	property string w1Id
	property bool busy: true
	property real temperatureScale: 0.001

	property int error
	property real temperature
	property bool plugged
	property int crc
	property date timestamp

	Component.onCompleted: {
		Private.loadData()
		Private.updateError()
		device.ds18b20[w1Id].valueUpdated.connect(Private.onValueUpdated)
		device.ds18b20[w1Id].errorChanged.connect(Private.updateError)
		device.ds18b20[w1Id].awake()
	}

	Component.onDestruction: {
		device.ds18b20[w1Id].errorChanged.disconnect(Private.updateError)
		device.ds18b20[w1Id].valueUpdated.disconnect(Private.onValueUpdated)
		device.ds18b20[w1Id].rest()
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
