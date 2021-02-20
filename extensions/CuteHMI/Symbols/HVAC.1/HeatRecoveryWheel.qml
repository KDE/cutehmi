import QtQuick 2.5

import CuteHMI.GUI 1.0

/**
  Heat recovery wheel.
  */
Element {
	id: root

	implicitWidth: units.quadrat * 0.5
	implicitHeight: units.quadrat * 2.0

	property int segments: 16

	property bool clockwise: true

	property real implicitRpm: 10

	property real rpm: active ? implicitRpm : 0

	property Component frame: Component {
		SymbolCanvas {
			element: root

			onPaint: {
				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = root.color.stroke
				ctx.fillStyle = root.color.shade
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

	property Component wheel: Component {
		SymbolCanvas {
			element: root

			property real rotation: 0.0

			property real wheelWidth: width * 0.75

			onPaint: {
				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = root.color.stroke
				ctx.fillStyle = root.color.fill
				ctx.lineWidth = units.strokeWidth

				var offset = units.strokeWidth / 2.0

				// Draw background.
				ctx.rect(offset + (width - wheelWidth) * 0.5, offset, width - units.strokeWidth - (width - wheelWidth), height - units.strokeWidth)
				ctx.stroke()
				ctx.fill()

				// Draw segments.
				var r = height * 0.5
				var angle = 180 / segments
				for (var i = 0; i < segments; i++) {
					var currentAngle = (i * angle + rotation) % 180
					currentAngle -= 90
					currentAngle *= Math.PI / 180
					var y = height * 0.5 + Math.sin(currentAngle) * r
					ctx.moveTo(offset + (width - wheelWidth) * 0.5, y)
					ctx.lineTo(width - units.strokeWidth - (width - wheelWidth) * 0.5, y)
					ctx.stroke()
				}

				ctx.restore()
			}

			onRotationChanged: requestPaint()

			Connections	{
				target: root

				function onRpmChanged() {
					handleRotation()
				}

				function onClockwiseChanged() {
					handleRotation()
				}

				function handleRotation() {
					if (clockwise) {
						rotationAnimation.from = rotation % 360
						rotationAnimation.to = rotation % 360 + 360 * Math.ceil(root.rpm)
					} else {
						rotationAnimation.to = rotation % 360
						rotationAnimation.from = rotation % 360 + 360 * Math.ceil(root.rpm)
					}

					if (root.rpm)
						rotationAnimation.restart()
					else
						rotationAnimation.stop()
				}

				Component.onCompleted: handleRotation()
			}

			Connections {
				target: root

				function onSegmentsChanged() {
					requestPaint()
				}
			}

			RotationAnimation on rotation {
				id: rotationAnimation

				duration: 60000 // 1 min = 60000 ms
				loops: Animation.Infinite
				direction: clockwise ? RotationAnimation.Clockwise : RotationAnimation.Counterclockwise
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
