import QtQuick 2.0
import QtQuick.Controls 1.3

import CuteHMI.Modbus 1.0

Item
{
	id: root

	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property var device
	property int address
	property int encoding: ModbusHoldingRegister.INT16
	property real valueScale: 1.0
	property bool busy: true
	property alias busyIndicator: busyIndicator

	ExtBusyIndicator
	{
		id: busyIndicator

		anchors.centerIn: parent
		running: root.busy
	}

	Component.onCompleted : {
		parent.value = valueScale * device.ir[address].value(encoding)
		device.ir[address].valueUpdated.connect(updatedValue)
	}

	Component.onDestruction: {
		device.ir[address].valueUpdated.disconnect(updatedValue)
	}

	function updatedValue()
	{
		parent.value = valueScale * device.ir[address].value(encoding)
		busy = false
	}
}
