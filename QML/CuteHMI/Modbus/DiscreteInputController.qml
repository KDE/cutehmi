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
