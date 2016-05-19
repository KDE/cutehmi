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

	property int _writeCtr: 0

	ExtBusyIndicator
	{
		id: busyIndicator

		running: root.busy
		centerIn: parent
	}

	Component.onCompleted : {
		parent.value = valueScale * device.r[address].value(encoding)
		if (parent.valueChanged !== undefined)
			parent.valueChanged.connect(changeValue)
		device.r[address].valueWritten.connect(writtenValue)
		device.r[address].valueUpdated.connect(updatedValue)
		device.r[address].valueRequested.connect(requestedValue)
	}

	Component.onDestruction: {
		if (parent.valueChanged !== undefined)
			parent.valueChanged.disconnect(changeValue)
		device.r[address].valueRequested.disconnect(requestedValue)
		device.r[address].valueUpdated.disconnect(updatedValue)
		device.r[address].valueWritten.disconnect(writtenValue)
	}

	function changeValue()
	{
		device.r[address].requestValue(parent.value / valueScale, encoding)
	}

	function requestedValue()
	{
		busy = true
		_writeCtr++
	}

	function writtenValue()
	{
		_writeCtr--
	}

	function updatedValue()
	{
		if (_writeCtr > 0)
			return;

		// Value may get updated to a different value than requested or it may get updated by a different controller.
		// This may cause subsequent emission of valueChanged signal, so disconnect it temporarily.
		if (parent.valueChanged !== undefined)	// Some parents may not have valueChanged signal.
			parent.valueChanged.disconnect(changeValue)
		parent.value = valueScale * device.r[address].value(encoding)
		if (parent.valueChanged !== undefined)	// Some parents may not have valueChanged signal.
			parent.valueChanged.connect(changeValue)
		busy = false
	}
}

