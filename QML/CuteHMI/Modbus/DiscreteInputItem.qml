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
	property bool busy: true
	property alias busyIndicator: busyIndicator

	ExtBusyIndicator
	{
		id: busyIndicator

		running: root.busy
		centerIn: parent
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

