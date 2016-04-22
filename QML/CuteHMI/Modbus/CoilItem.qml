import QtQuick 2.0
import CuteHMI.Modbus 1.0
import QtQuick.Controls 1.3

/**
  Modbus coil item. This item is intended to interact with parent item in which it can be placed.
  Parent item must provide following properties:
		- bool checked - this property will be set to @p true or @p false, depending on coil status.
		.
  In addition parent item may provide:
		- signal checkedChanged() - when this signal is emitted a request will be made to update the coil with actual @a parent.checked value.
		.
  */
Item
{
	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property var device
	property int address
	property bool busy: true

	property int _writeCtr: 0

	BusyIndicator
	{
		id: busyIndicator

		anchors.centerIn: parent
		running: parent.busy
	}

	Component.onCompleted : {
		if (parent.checkedChanged !== undefined)
			parent.checkedChanged.connect(changeValue)
		device.b[address].valueWritten.connect(writtenValue)
		device.b[address].valueUpdated.connect(updatedValue)
		device.b[address].valueRequested.connect(requestedValue)
	}

	Component.onDestruction: {
		if (parent.checkedChanged !== undefined)
			parent.checkedChanged.disconnect(changeValue)
		device.b[address].valueRequested.disconnect(requestedValue)
		device.b[address].valueUpdated.disconnect(updatedValue)
		device.b[address].valueWritten.disconnect(writtenValue)
	}

	function changeValue()
	{
		console.log("CoilItem::changeValue()")

		device.b[address].requestValue(parent.checked)
	}

	function requestedValue()
	{
		console.log("CoilItem::requestValue()")

		busy = true
		_writeCtr++
	}

	function writtenValue()
	{
		console.log("CoilItem::writtenValue()")

		_writeCtr--
	}

	function updatedValue()
	{
		console.log("CoilItem::updatedValue()")

		if (_writeCtr > 0)
			return;

		if (parent.checkedChanged !== undefined)	// Some parents may not have clicked signal.
			parent.checkedChanged.disconnect(changeValue)
		parent.checked = device.b[address].value()
		if (parent.checkedChanged !== undefined)	// Some parents may not have clicked signal.
			parent.checkedChanged.connect(changeValue)
		busy = false
	}
}

