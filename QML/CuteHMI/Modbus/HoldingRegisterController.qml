import QtQuick 2.0

import CuteHMI.Modbus 1.0

QtObject
{
	id: root

	default property var delegate
	property var device
	property int address
	property int encoding: ModbusHoldingRegister.INT16
	property real valueScale: 1.0
	property bool busy: true

	property int _writeCtr: 0

	Component.onCompleted : {
		delegate.value = valueScale * device.r[address].value(encoding)
		if (delegate.valueChanged !== undefined)
			delegate.valueChanged.connect(changeValue)
		device.r[address].valueWritten.connect(writtenValue)
		device.r[address].valueUpdated.connect(updatedValue)
		device.r[address].valueRequested.connect(requestedValue)
	}

	Component.onDestruction: {
		if (delegate.valueChanged !== undefined)
			delegate.valueChanged.disconnect(changeValue)
		device.r[address].valueRequested.disconnect(requestedValue)
		device.r[address].valueUpdated.disconnect(updatedValue)
		device.r[address].valueWritten.disconnect(writtenValue)
	}

	function changeValue()
	{
		device.r[address].requestValue(delegate.value / valueScale, encoding)
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
		if (delegate.valueChanged !== undefined)	// Some delegates may not have valueChanged signal.
			delegate.valueChanged.disconnect(changeValue)
		delegate.value = valueScale * device.r[address].value(encoding)
		if (delegate.valueChanged !== undefined)	// Some delegates may not have valueChanged signal.
			delegate.valueChanged.connect(changeValue)
		busy = false
	}
}

