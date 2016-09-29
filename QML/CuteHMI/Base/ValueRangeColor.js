
var currentRange = 0

function pickColor()
{
	if (isNaN(value))
		color = nanColor
	else {
		if (!(value >= ranges[currentRange][0] && (value <= ranges[currentRange][1])))
			for (var i = 0; i < ranges.length; i++)
				if (value >= ranges[i][0] && ( value <= ranges[i][1])) {
					currentRange = i
					break
				}
		color = colors[currentRange]
	}
}
