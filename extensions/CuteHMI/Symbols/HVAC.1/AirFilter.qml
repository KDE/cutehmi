import QtQuick 2.5

import CuteHMI.GUI 1.0

/**
  Air filter.
  */
Element {
	id: root

	implicitWidth: units.quadrat * 0.5
	implicitHeight: units.quadrat * 1.5
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
				ctx.lineWidth = units.strokeWidth

				var offset = units.strokeWidth / 2.0

				// Draw case.
				ctx.rect(offset, offset, width - units.strokeWidth, height - units.strokeWidth)
				ctx.fill()
				ctx.stroke()

				// Draw dirt.
				ctx.fillStyle = root.color.shade
				ctx.beginPath()
				var dirtWidth = (width - 2 * units.strokeWidth) * fill
				ctx.fillRect(width - units.strokeWidth - dirtWidth, units.strokeWidth, dirtWidth, height - 2 * units.strokeWidth)
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
				ctx.lineWidth = units.strokeWidth

				// Draw pockets.
				var offset = units.strokeWidth / 2.0
				var pocketHeight = (height - units.strokeWidth) / pockets

				ctx.beginPath()
				var y = pocketHeight / 2.0
				ctx.moveTo(width - units.strokeWidth, offset)
				ctx.lineTo(offset, offset)
				ctx.lineTo(width - units.strokeWidth, y)
				for (var i = 1; i < pockets; i++) {
					y += pocketHeight / 2.0
					ctx.lineTo(offset, y)
					y += pocketHeight / 2.0
					ctx.lineTo(width - units.strokeWidth, y)
				}
				ctx.lineTo(offset, height - offset)
				ctx.lineTo(width - units.strokeWidth, height - offset)
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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
