import QtQuick 2.0

import CuteHMI.Modbus 1.0

QtObject
{
	id: root

	default property var delegate
	property var device
	property int address
	property bool busy: true

	Component.onCompleted : {
		delegate.checked = device.ib[address].value()
		device.ib[address].valueUpdated.connect(updatedValue)
		device.ib[address].awake()
	}

	Component.onDestruction: {
		device.ib[address].valueUpdated.disconnect(updatedValue)
		device.ib[address].rest()
	}

	function updatedValue()
	{
		delegate.checked = device.ib[address].value()
		busy = false
	}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
