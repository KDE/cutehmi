import QtQuick 2.0

import CuteHMI.GUI 1.0

/**
  Centrifugal fan.
  */
Element {
	id: root

	implicitWidth: units.quadrat * 1.25
	implicitHeight: units.quadrat

	property bool mirror: false
	property real implicitRpm: 30
	property real rpm: active ? implicitRpm : 0

	property Component housing: Component {
		SymbolCanvas {
			transform: Scale { origin.x: width * 0.5; xScale: root.mirror ? -1 : 1 }

			element: root

			onPaint: {
				var diameter = root.internal.diameter

				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = color.stroke
				ctx.fillStyle = color.tint
				ctx.lineWidth = units.strokeWidth

				var offset = units.strokeWidth * 0.5
				var x = width * 0.5
				var y = height * 0.5
				var r = diameter * 0.5
				var housingWidth = width - offset
				var exhaustWidth = (width - diameter) * 0.5
				var exhaustHeight = diameter * 0.375

				// Draw housing.
				ctx.arc(x, y, r - offset, 0.0, 1.5 * Math.PI, false)
				ctx.lineTo(housingWidth, offset)
				ctx.lineTo(housingWidth, exhaustHeight)
				ctx.lineTo(diameter + exhaustWidth - offset, exhaustHeight)
				ctx.lineTo(diameter + exhaustWidth - offset, y)
				ctx.fill()
				ctx.stroke()

				ctx.restore();
			}

			Connections {
				target: root.internal

				function onDiameterChanged() {
					requestPaint()
				}
			}
		}
	}

	property Component wheel: Component {
		SymbolCanvas {
			transform: Scale { origin.x: width * 0.5; xScale: root.mirror ? -1 : 1 }

			element: root

			onPaint: {
				var wheelDiameter = root.internal.wheelDiameter

				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = color.stroke
				ctx.fillStyle = color.fill
				ctx.lineWidth = units.strokeWidth

				// Draw fan wheel.
				var x = width * 0.5
				var y = height * 0.5
				var wheelR = wheelDiameter * 0.5

				ctx.arc(x, y, wheelR, 0.0, 2 * Math.PI, false)
				ctx.fill()
				ctx.stroke()

				// Draw bearings
				ctx.beginPath()
				ctx.arc(x, y, units.strokeWidth, 0.0, 2 * Math.PI, false)
				ctx.stroke()

				// Draw blades.
				var angle = Math.PI / 6.0
				var sinAngle = Math.sin(angle)
				var cosAngle = Math.cos(angle)
				var x1 = 0.0
				var y1 = units.strokeWidth
				var x2 = 0.0
				var y2 = wheelR

				ctx.beginPath()
				ctx.moveTo(x + x1, y + y1)
				ctx.lineTo(x + x2, y + y2)
				ctx.stroke()
				for (var curAngle = angle; curAngle < 2.0 * Math.PI; curAngle += angle) {
					var newX1 = x1 * cosAngle - y1 * sinAngle
					y1 = x1 * sinAngle + y1 * cosAngle
					x1 = newX1
					var newX2 = x2 * cosAngle - y2 * sinAngle
					y2 = x2 * sinAngle + y2 * cosAngle
					x2 = newX2
					ctx.beginPath()
					ctx.moveTo(x + x1, y + y1)
					ctx.lineTo(x + x2, y + y2)
					ctx.stroke()
				}

				ctx.restore();
			}

			Connections {
				target: root

				function onRpmChanged() {
					handleRotation()
				}

				function handleRotation() {
					rotationAnimation.from = rotation % 360
					rotationAnimation.to = rotation % 360 + 360 * Math.ceil(root.rpm)
					if (root.rpm)
						rotationAnimation.restart()
					else
						rotationAnimation.stop()
				}

				Component.onCompleted: handleRotation()
			}

			Connections {
				target: root.internal

				function onWheelDiameterChanged() {
					requestPaint()
				}
			}

			RotationAnimation on rotation {
				id: rotationAnimation

				duration: 60000 // 1 min = 60000 ms
				loops: Animation.Infinite
			}
		}
	}

	property QtObject internal: QtObject {
		property real diameter: root.height
		property real wheelDiameter: diameter * 0.625
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: housing
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: wheel
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
