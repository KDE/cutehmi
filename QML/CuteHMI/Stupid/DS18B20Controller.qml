import QtQuick 2.0

import CuteHMI.Stupid 1.0

QtObject
{
	id: root

//	default property var delegate
	property var device
	property string w1Id
	property bool busy: true
	property real temperatureScale: 0.001

	property int error
	property real temperature
	property bool plugged
	property int crc
	property date timestamp

	Component.onCompleted : {
		_loadData()
		device.ds18b20[w1Id].valueUpdated.connect(_updatedValue)
		device.ds18b20[w1Id].errorChanged.connect(_updateError)
	}

	Component.onDestruction: {
		device.ds18b20[w1Id].valueUpdated.disconnect(_updatedValue)
		device.ds18b20[w1Id].errorChanged.disconnect(_updateError)
	}

	function _updateError()
	{
		error = device.ds18b20[w1Id].error
	}

	function _updatedValue(valueTypes)
	{
		// Currently valueTypes flags are ignored as DS18B20 always updates all the values.
		_loadData()
		busy = false
	}

	function _loadData()
	{
		var dev = device.ds18b20[w1Id]
		temperature = temperatureScale * dev.temperature()
		plugged = dev.plugged()
		crc = dev.crc()
		timestamp = dev.timestamp()
	}
}
