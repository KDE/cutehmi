import QtQuick 2.0

import CuteHMI.Stupid 1.0

import "DS18B20Controller.js" as Private

QtObject
{
	id: root

	property var device
	property string w1Id
	property bool busy: true
	property real temperatureScale: 0.001

	property int error
	property real temperature
	property bool plugged
	property int crc
	property date timestamp
onErrorChanged: console.log(w1Id + " error: " + error)
	Component.onCompleted: {
		Private.loadData()
		Private.updateError()
		device.ds18b20[w1Id].valueUpdated.connect(Private.updatedValue)
		device.ds18b20[w1Id].errorChanged.connect(Private.updateError)
		device.ds18b20[w1Id].awake()
	}

	Component.onDestruction: {
		device.ds18b20[w1Id].errorChanged.disconnect(Private.updateError)
		device.ds18b20[w1Id].valueUpdated.disconnect(Private.updatedValue)
		device.ds18b20[w1Id].rest()
	}
}
