import QtQuick 2.0
import CuteHMI.Modbus 1.0
import QtQuick.Controls 1.3

Item
{
	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property var device
	property int address
	property bool busy: true

	BusyIndicator
	{
		id: busyIndicator

		anchors.centerIn: parent
		running: parent.busy
	}

	Component.onCompleted : {
		parent.checked = device.ib[address].value()
		device.ib[address].valueUpdated.connect(updatedValue)
	}

	Component.onDestruction: {
		device.ib[address].valueUpdated.disconnect(updatedValue)
	}

	function updatedValue()
	{
		parent.checked = device.ib[address].value()
		busy = false
	}
}

