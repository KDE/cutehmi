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
	property bool readOnly: false

	property int _writeCtr: 0

	onReadOnlyChanged: readOnly ? delegate.valueChanged.disconnect(changeValue) : delegate.valueChanged.connect(changeValue)

	Component.onCompleted : {
		delegate.value = valueScale * device.r[address].value(encoding)
		if (!readOnly)
			delegate.valueChanged.connect(changeValue)
		device.r[address].valueWritten.connect(writtenValue)
		device.r[address].valueUpdated.connect(updatedValue)
		device.r[address].valueRequested.connect(requestedValue)
		device.r[address].awake()
	}

	Component.onDestruction: {
		if (!readOnly)
			delegate.valueChanged.disconnect(changeValue)
		device.r[address].valueRequested.disconnect(requestedValue)
		device.r[address].valueUpdated.disconnect(updatedValue)
		device.r[address].valueWritten.disconnect(writtenValue)
		device.r[address].rest()
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
		if (!readOnly)
			delegate.valueChanged.disconnect(changeValue)
		delegate.value = valueScale * device.r[address].value(encoding)
		if (!readOnly)
			delegate.valueChanged.connect(changeValue)
		busy = false
	}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
