function updateError()
{
	error = device.ds18b20[w1Id].error
}

function onValueUpdated(valueTypes)
{
	// Currently valueTypes flags are ignored as DS18B20 always updates all the values.
	loadData()
	busy = false
}

function loadData()
{
	var dev = device.ds18b20[w1Id]
	temperature = temperatureScale * dev.temperature()
	plugged = dev.plugged()
	crc = dev.crc()
	timestamp = dev.timestamp()
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
