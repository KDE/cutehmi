import QtQuick 2.0

import CuteHMI.Modbus 1.0

QtObject
{
	id: root

	default property var delegate
	property var device
	property int address
	property int encoding: ModbusInputRegister.INT16
	property real valueScale: 1.0
	property bool busy: true

	Component.onCompleted : {
		delegate.value = valueScale * device.ir[address].value(encoding)
		device.ir[address].valueUpdated.connect(updatedValue)
	}

	Component.onDestruction: {
		device.ir[address].valueUpdated.disconnect(updatedValue)
	}

	function updatedValue()
	{
		delegate.value = valueScale * device.ir[address].value(encoding)
		busy = false
	}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
