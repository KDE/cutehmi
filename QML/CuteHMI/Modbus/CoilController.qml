import QtQuick 2.0

import CuteHMI.Modbus 1.0

/*!
  \qmltype CoilController
  \inqmlmodule CuteHMI.Modbus
  \since CuteHMI.Modbus 1.0
  \brief Modbus coil controller.

  Coil controller is intended to interact with modbus \a device and \a delegate, which may then pass data to frontend model and view.
  Conceptually this looks like following:
  \div {class="ascii-art"}
	backend model (modbus \a device) \unicode 0x21C4 CoilController \unicode 0x21C4 \a delegate \unicode 0x21C4 frontend model \unicode 0x2192 view.
  \enddiv
  */
QtObject
{
	id: root

	/*!
	  \qmlproperty var CoilController::delegate

	  Specifies delegate to interact with controller. Every \a delegate must provide following properties:
	  \list
		\li \c bool \a checked - this property will be set to \c true or \c false, depending on coil status.
		\li \c signal \a checkedChanged() - when this signal is emitted a request will be made to update the coil with actual \a delegate.checked value.
	  \endlist
	  */
	default property var delegate

	/*!
	  \qmlproperty var CoilController::device

	  Specifies modbus device. This is a context property, which is provided by plugin and configured via CuteHMI project.
	  */
	property var device

	/*!
	  \qmlproperty int CoilController::address

	  Coil address.
	  */
	property int address

	/*!
	  \qmlproperty bool CoilController::readOnly

	  Toggles read only mode. If this property is set to \c true controller will ignore \a delegate.checkedChanged() signal.
	  This means requests will not be made to update coil value in the modbus device. Default is \c false.
	  */
	property bool readOnly: false

	/*!
	  \qmlproperty bool CoilController::busy

	  Busy flag. This flag can be used to improve UI experience. The property is initialized to \c true. It changes to \c false
	  once the data has been read from the modbus device. It goes back to \c true whenever a request is made to write a new value
	  to the modbus device.
	  */
	property bool busy: true

	/*!
	  \internal
	  */
	property int _writeCtr: 0

	/*!
	  \internal
	  */
	function changeValue()
	{
		device.b[address].requestValue(delegate.checked)
	}

	/*!
	  \internal
	  */
	function requestedValue()
	{
		busy = true
		_writeCtr++
	}

	/*!
	  \internal
	  */
	function writtenValue()
	{
		_writeCtr--
	}

	/*!
	  \internal
	  */
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

	onReadOnlyChanged: readOnly ? delegate.checkedChanged.disconnect(changeValue) : delegate.checkedChanged.connect(changeValue)

	Component.onCompleted : {
		delegate.checked = device.b[address].value()
		if (!readOnly)
			delegate.checkedChanged.connect(changeValue)
		device.b[address].valueWritten.connect(writtenValue)
		device.b[address].valueUpdated.connect(updatedValue)
		device.b[address].valueRequested.connect(requestedValue)
		device.b[address].awake()
	}

	Component.onDestruction: {
		if (!readOnly)
			delegate.checkedChanged.disconnect(changeValue)
		device.b[address].valueRequested.disconnect(requestedValue)
		device.b[address].valueUpdated.disconnect(updatedValue)
		device.b[address].valueWritten.disconnect(writtenValue)
		device.b[address].rest()
	}
}

