import QtQuick 2.0

import CuteHMI.GUI 1.0

/**
  Pump.
  */
Element {
	id: root

	implicitWidth: units.quadrat
	implicitHeight: units.quadrat

	property real implicitRpm: 30

	property real rpm: active ? implicitRpm : 0

	property Component housing: Component {
		SymbolCanvas {
			element: root

			onPaint: {
				var diameter = root.internal.diameter
				var innerDiameter = root.internal.innerDiameter

				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = color.tint
				ctx.lineWidth = (diameter - innerDiameter) * 0.5
				ctx.arc(width * 0.5, height * 0.5, (diameter + innerDiameter) * 0.25, 0.0, 2 * Math.PI, false)
				ctx.stroke()
				ctx.closePath()

				ctx.beginPath()
				ctx.strokeStyle = color.stroke
				ctx.lineWidth = units.strokeWidth
				ctx.arc(width * 0.5, height * 0.5, (diameter - units.strokeWidth) * 0.5, 0.0, 2 * Math.PI, false)
				ctx.stroke()

				ctx.restore();
			}

			Connections {
				target: root.internal

				function onDiameterChanged() {
					requestPaint()
				}

				function onInnerDiameterChanged() {
					requestPaint()
				}
			}
		}
	}

	property Component rotor: Component {
		SymbolCanvas {
			element: root

			onPaint: {
				var diameter = root.internal.diameter
				var innerDiameter = root.internal.innerDiameter

				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = color.shade
				ctx.lineWidth = (diameter - innerDiameter) * 0.5 - units.strokeWidth

				// Draw vanes.
				var arcR = (diameter + innerDiameter) * 0.25 - units.strokeWidth * 0.5
				var angle = Math.PI / 6.0
				for (var curAngle = 0; curAngle < 2 * Math.PI; curAngle += 2 * angle) {
					ctx.beginPath()
					ctx.arc(width * 0.5, height * 0.5, arcR, curAngle, curAngle + angle)
					ctx.stroke()
					ctx.closePath()
				}
				ctx.restore();
			}

			Connections	{
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

				function onDiameterChanged() {
					requestPaint()
				}

				function onInnerDiameterChanged() {
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


	property Component symbol: Component {
		SymbolCanvas {
			element: root

			onPaint: {
				var diameter = root.internal.diameter
				var innerDiameter = root.internal.innerDiameter

				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = color.stroke
				ctx.lineWidth = units.strokeWidth

				var lineOffset = units.strokeWidth * 0.5
				var symbolOffset = (diameter - innerDiameter) * 0.5
				var insetDiameter = innerDiameter - units.strokeWidth

				ctx.translate(symbolOffset, symbolOffset)

				// Draw circle.
				ctx.fillStyle = color.blank
				ctx.ellipse(lineOffset, lineOffset, insetDiameter, insetDiameter)
				ctx.fill()
				ctx.stroke()

				// Draw inner triangle.
				ctx.fillStyle = color.fill
				ctx.beginPath();
				ctx.moveTo(innerDiameter - lineOffset, innerDiameter * 0.5)
				ctx.lineTo(innerDiameter * 0.25 + lineOffset, innerDiameter * ( 2.0 + Math.sqrt(3.0)) * 0.25 - lineOffset)
				ctx.lineTo(innerDiameter * 0.25 + lineOffset, innerDiameter * ( 2.0 - Math.sqrt(3.0)) * 0.25 + lineOffset)
				ctx.closePath()
				ctx.fill()
				ctx.stroke()

				ctx.restore();
			}

			Connections {
				target: root.internal

				function onDiameterChanged() {
					requestPaint()
				}

				function onInnerDiameterChanged() {
					requestPaint()
				}
			}
		}
	}

	property QtObject internal: QtObject {
		property real diameter: Math.min(root.width, root.height)
		property real innerDiameter: diameter * 0.75
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: housing
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: rotor
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: symbol
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
