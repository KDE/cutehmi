import QtQuick 2.5

import CuteHMI.GUI 1.0

/**
  Blade damper.
  */
Element {
	id: root

	implicitWidth: horizontal ? units.quadrat * 1.5 : units.quadrat * 0.25
	implicitHeight: horizontal ? units.quadrat * 0.25 : units.quadrat * 1.5
	active: true

	property int blades: 6

	property real value: 0.5

	property bool opposedBlade: true

	property bool mirror: false

	property bool horizontal: false

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
				ctx.lineWidth = units.strokeWidth

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

				function onBladesChanged() {
					requestPaint()
				}

				function onValueChanged() {
					requestPaint()
				}

				function onOpposedBladeChanged() {
					requestPaint()
				}

				function onMirrorChanged() {
					requestPaint()
				}
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

//(c)C: Copyright © 2020-2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
