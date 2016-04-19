import QtQuick 2.0
import CuteHMI.Modbus 1.0
import QtQuick.Controls 1.3

Item
{
//	implicitWidth: 50
//	implicitHeight: 50
	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property var device
	property int address
	property int encoding: ModbusHoldingRegister.INT16
	property real valueScale: 1.0

	property string _oldState
	property int _writeCtr: 0

	BusyIndicator
	{
		id: busyIndicator

		anchors.centerIn: parent
	}

	Component.onCompleted : {
		if (parent.valueChanged !== undefined)
//			parent.valueChanged.connect(requestValue)
			parent.valueChanged.connect(changeValue)
		device.r[address].valueWritten.connect(writtenValue)
		device.r[address].valueUpdated.connect(updateValue)
		device.r[address].valueRequested.connect(requestValue)
		_oldState = parent.state
		parent.state = "busy"
		busyIndicator.running = true
	}

	Component.onDestruction: {
		device.r[address].valueRequested.disconnect(requestValue)
		device.r[address].valueUpdated.disconnect(updateValue)
		device.r[address].valueWritten.disconnect(writtenValue)
	}

	function changeValue()
	{
		device.r[address].requestValue(parent.value / valueScale, encoding)
	}

	function requestValue()
	{
		console.log("requestValue()")

		if (parent.state !== "busy") {
			_oldState = parent.state
			parent.state = "busy"
			busyIndicator.running = true
		}
		_writeCtr++
//		device.r[address].requestValue(parent.value, encoding)
	}

	function writtenValue()
	{
		console.log("writtenValue()")

		_writeCtr--
	}

	function updateValue()
	{
		console.log("updateValue()")

		if (_writeCtr > 0)
			return;

		// Value may get updated right after doing request to a different value or it may get updated by a different controller.
		// This may cause subsequent emission of valueChanged signal, so disconnect it temporarily.
		if (parent.valueChanged !== undefined)	// Some parents may not have valueChanged signal.
//			parent.valueChanged.disconnect(requestValue)
			parent.valueChanged.disconnect(changeValue)
		parent.value = valueScale * device.r[address].value(encoding)
		if (parent.valueChanged !== undefined)	// Some parents may not have valueChanged signal.
//			parent.valueChanged.connect(requestValue)
			parent.valueChanged.connect(changeValue)
		// Restore the old state if it has not changed in a meanwhile.
		if (parent.state === "busy")
			parent.state = _oldState
		busyIndicator.running = false
	}
}

