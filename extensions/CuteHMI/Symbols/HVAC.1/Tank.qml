import QtQuick 2.0

import CuteHMI.GUI 1.0

/**
  Tank.
  */
Element {
	id: root

	implicitWidth: units.quadrat * 0.75
	implicitHeight: units.quadrat * 1.5

	active: true

	property real headRatio: 0.25

	property real level: 0.0

	property Component shell: Component {
		SymbolCanvas {
			element: root

			onPaint: {
				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = root.color.stroke
				ctx.fillStyle = root.color.fill
				ctx.lineWidth = units.strokeWidth

				var offset = units.strokeWidth / 2.0
				var headRadius = height * root.headRatio
				var shellHeight = height - headRadius - units.strokeWidth

				// Draw top ellipsoidal head.
				ctx.ellipse(offset, offset, width - units.strokeWidth, headRadius)
				ctx.fill()
				ctx.stroke()

				// Draw bottom ellipsoidal head.
				ctx.ellipse(offset, offset + shellHeight, width - units.strokeWidth, headRadius)
				ctx.fill()
				ctx.stroke()

				// Draw shell.
				ctx.beginPath()
				ctx.rect(offset, offset + headRadius * 0.5, width - units.strokeWidth, shellHeight)
				ctx.fill()
				ctx.stroke()

				ctx.restore()
			}

			Connections {
				target: root

				function onHeadRatioChanged() {
					requestPaint()
				}
			}
		}
	}

	property Component liquid: Component {
		Item {
			property real headRadius: height * root.headRatio
			property real shellHeight: height - headRadius - units.strokeWidth
			property real liquidY: (height - 2 * units.strokeWidth) * (1.0 - level)

			// Liquid in heads.
			SymbolCanvas {
				id: headsLiquidCanvas

				anchors.fill: parent

				element: root

				onPaint: {
					var ctx = getContext('2d')
					ctx.save()
					ctx.reset()

					ctx.strokeStyle = root.color.stroke
					ctx.fillStyle = root.color.shade
					ctx.lineWidth = units.strokeWidth

					ctx.ellipse(units.strokeWidth, units.strokeWidth, width - 2 * units.strokeWidth, headRadius - units.strokeWidth)
					ctx.ellipse(units.strokeWidth, units.strokeWidth + shellHeight, width - 2 * units.strokeWidth, headRadius - units.strokeWidth)
					ctx.clip()

					ctx.beginPath()
					ctx.rect(0, liquidY + units.strokeWidth, width, height - liquidY - 2 * units.strokeWidth)
					ctx.fill()

					if (level != 0 && level != 1) {
						ctx.beginPath()
						ctx.moveTo(0, liquidY + units.strokeWidth)
						ctx.lineTo(width, liquidY + units.strokeWidth)
						ctx.stroke()
					}

					ctx.restore()
				}
			}

			// Liquid in a shell.
			SymbolCanvas {
				id: shellLiquidCanvas

				anchors.fill: parent

				element: root

				onPaint:  {
					var ctx = getContext('2d')
					ctx.save()
					ctx.reset()

					ctx.strokeStyle = root.color.stroke
					ctx.fillStyle = root.color.shade
					ctx.lineWidth = units.strokeWidth

					ctx.rect(units.strokeWidth, units.strokeWidth + headRadius * 0.5, width - 2 * units.strokeWidth, shellHeight)
					ctx.clip()

					ctx.beginPath()
					ctx.rect(0, liquidY + units.strokeWidth, width, height - liquidY - 2 * units.strokeWidth)
					ctx.fill()

					if (level != 0 && level != 1) {
						ctx.beginPath()
						ctx.moveTo(0, liquidY + units.strokeWidth)
						ctx.lineTo(width, liquidY + units.strokeWidth)
						ctx.stroke()
					}
				}
			}

			Connections {
				target: root

				function onHeadRatioChanged() {
					shellLiquidCanvas.requestPaint()
					headsLiquidCanvas.requestPaint()
				}

				function onLevelChanged() {
					shellLiquidCanvas.requestPaint()
					headsLiquidCanvas.requestPaint()
				}
			}
		}
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: shell
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: liquid
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
