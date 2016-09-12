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
