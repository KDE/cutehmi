import QtQuick 2.5

import CuteHMI.GUI 0.0

/**
  Active symbol of air filter.
  */
Element
{
	id: root

	implicitWidth: CuteApplication.theme.units.quadrat * 0.5
	implicitHeight: CuteApplication.theme.units.quadrat * 1.5
	active: true
	warning: fill >= dirtyWarning
	alarm: fill >= dirtyAlarm

	property bool mirror: false

	// Number of filter pockets.
	property int pockets: 5

	// Fill level (0.0 - 1.0).
	property real fill: 0.0

	property real dirtyWarning: 0.75
	property real dirtyAlarm: 0.9

	property Component frame: Component {
		SymbolCanvas {
			transform: Scale { origin.x: width * 0.5; xScale: root.mirror ? -1 : 1 }

			element: root

			onPaint: {
				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = root.color.stroke
				ctx.fillStyle = root.color.fill
				ctx.lineWidth = strokeWidth

				var offset = strokeWidth / 2.0

				// Draw case.
				ctx.rect(offset, offset, width - strokeWidth, height - strokeWidth)
				ctx.fill()
				ctx.stroke()

				// Draw dirt.
				ctx.fillStyle = root.color.shade
				ctx.beginPath()
				var dirtWidth = (width - 2 * strokeWidth) * fill
				ctx.fillRect(width - strokeWidth - dirtWidth, strokeWidth, dirtWidth, height - 2 * strokeWidth)
				ctx.fill()

				ctx.restore()
			}

			Connections {
				target: root
				onFillChanged: requestPaint()
			}
		}
	}

	property Component content: Component {
		SymbolCanvas {
			transform: Scale { origin.x: width * 0.5; xScale: root.mirror ? -1 : 1 }

			element: root

			onPaint: {
				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = root.color.stroke
				ctx.fillStyle = root.color.tint
				ctx.lineWidth = strokeWidth

				// Draw pockets.
				var offset = strokeWidth / 2.0
				var pocketHeight = (height - strokeWidth) / pockets

				ctx.beginPath()
				var y = pocketHeight / 2.0
				ctx.moveTo(width - strokeWidth, offset)
				ctx.lineTo(offset, offset)
				ctx.lineTo(width - strokeWidth, y)
				for (var i = 1; i < pockets; i++) {
					y += pocketHeight / 2.0
					ctx.lineTo(offset, y)
					y += pocketHeight / 2.0
					ctx.lineTo(width - strokeWidth, y)
				}
				ctx.lineTo(offset, height - offset)
				ctx.lineTo(width - strokeWidth, height - offset)
				ctx.fill()
				ctx.stroke()

				ctx.restore()
			}

			Connections {
				target: root
				onPocketsChanged: requestPaint()
			}
		}
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: frame
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: content
	}
}
