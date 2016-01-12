import QtQuick 2.0
import CuteHMI.Modbus 1.0

Item {
	property var device
	property int address
	property int encoding: ModbusHoldingRegister.INT16

	visible: false
	width: 50
	height: 50
	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	Component.onCompleted : {
		parent.valueChanged.connect(requestValue)
		device.r[address].valueUpdated.connect(updateValue)
		parent.enabled = false
	}

	function requestValue()
	{
		parent.enabled = false
		device.r[address].requestValue(parent.value, encoding)
	}

	function updateValue()
	{
		// Value may get updated right after doing request to a different value or it may get updated by different controller.
		// This may cause subsequent emission of valueChanged signal, so disconnect it temporarily.
		parent.valueChanged.disconnect(requestValue)
		parent.value = device.r[address].value(encoding)
		parent.valueChanged.connect(requestValue)
		parent.enabled = true
	}
}

