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
