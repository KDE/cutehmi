import QtQuick 2.5

import CuteHMI.GUI 0.0

/**
  Blade damper.
  */
Element {
	id: root

	implicitWidth: horizontal ? CuteApplication.theme.units.quadrat : CuteApplication.theme.units.quadrat * 0.25
	implicitHeight: horizontal ? CuteApplication.theme.units.quadrat * 0.25 : CuteApplication.theme.units.quadrat
	active: true

	property int blades: 4

	property real value: 0.5

	property bool opposedBlade: true

	property bool mirror: false

	property bool horizontal

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

				ctx.restore()
			}
		}
	}

	property Component mechanism: Component {
		SymbolCanvas {
			transform: [
				Scale { origin.x: width * 0.5; xScale: root.mirror ? -1 : 1 },
				Rotation { origin.x: root.height * 0.5; origin.y: root.height * 0.5; angle: horizontal ? -90 : 0 }
			]

			element: root

			property real bladeSize: width * 0.75

			property real bearingRadius: bladeSize * 0.125

			onPaint: {
				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = root.color.stroke
				ctx.fillStyle = root.color.stroke
				ctx.lineWidth = strokeWidth

				var bladeMargin = 0.5 * (width - bladeSize)
				var totalBladesHeight = root.blades * (bladeSize + bladeMargin) - bladeMargin
				var margin = 0.5 * (height - totalBladesHeight)

				var angle = value * Math.PI * 0.5
				ctx.translate(width * 0.5, margin + 0.5 * bladeSize)
				for (var i = 0; i < blades; i++) {
					// Draw bearing.
					ctx.beginPath()
					ctx.arc(0, 0, bearingRadius, 0, 2 * Math.PI, false)
					ctx.stroke()
					ctx.fill()

					// Draw blade.
					if (root.opposedBlade)
						angle = -angle
					ctx.rotate(angle)
					ctx.beginPath()
					ctx.moveTo(0, -bladeSize * 0.5)
					ctx.lineTo(0, bladeSize * 0.5)
					ctx.stroke()
					ctx.rotate(-angle)

					ctx.translate(0, bladeSize + bladeMargin)
				}

				ctx.restore()
			}

			Connections {
				target: root
				onBladesChanged: requestPaint()
				onValueChanged: requestPaint()
				onOpposedBladeChanged: requestPaint()
				onMirrorChanged: requestPaint()
			}
		}
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: frame
	}

	Loader {
		width: horizontal ? root.height : root.width
		height: horizontal ? root.width : root.height
		sourceComponent: mechanism
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
