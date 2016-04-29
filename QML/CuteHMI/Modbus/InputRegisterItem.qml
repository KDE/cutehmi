import QtQuick 2.0
import CuteHMI.Modbus 1.0
import QtQuick.Controls 1.3

Item
{
	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property var device
	property int address
	property int encoding: ModbusHoldingRegister.INT16
	property real valueScale: 1.0
	property bool busy: true

	BusyIndicator
	{
		id: busyIndicator

		anchors.centerIn: parent
		running: parent.busy
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
