import QtQuick 2.0

import CuteHMI.Modbus 1.0

/**
  Modbus coil controller. Controller is intended to interact with delegate, which may then pass data to frontend model and view.
  Conceptually this looks like following: backend model (modbus device) <-> controller <-> delegate <-> frontend model -> view.
  delegate must provide following properties:
		- bool checked - this property will be set to @p true or @p false, depending on coil status.
		.
  In addition delegate item may provide:
		- signal checkedChanged() - when this signal is emitted a request will be made to update the coil with actual @a delegate.checked value.
		.
  */
QtObject
{
	id: root

	default property var delegate
	property var device
	property int address
	property bool busy: true
	property bool readOnly: false

	property int _writeCtr: 0

	onReadOnlyChanged: readOnly ? delegate.checkedChanged.disconnect(changeValue) : delegate.checkedChanged.connect(changeValue)

	Component.onCompleted : {
		delegate.checked = device.b[address].value()
		if (!readOnly)
			delegate.checkedChanged.connect(changeValue)
		device.b[address].valueWritten.connect(writtenValue)
		device.b[address].valueUpdated.connect(updatedValue)
		device.b[address].valueRequested.connect(requestedValue)
	}

	Component.onDestruction: {
		if (!readOnly)
			delegate.checkedChanged.disconnect(changeValue)
		device.b[address].valueRequested.disconnect(requestedValue)
		device.b[address].valueUpdated.disconnect(updatedValue)
		device.b[address].valueWritten.disconnect(writtenValue)
	}

	function changeValue()
	{
		device.b[address].requestValue(delegate.checked)
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

		if (!readOnly)
			delegate.checkedChanged.disconnect(changeValue)
		delegate.checked = device.b[address].value()
		if (!readOnly)
			delegate.checkedChanged.connect(changeValue)
		busy = false
	}
}

