import QtQuick 2.0

import CuteHMI.GUI 1.0

/**
  Motor actuator.
  */
Element {
	id: root

	implicitWidth: units.quadrat * 0.5
	implicitHeight: units.quadrat * 0.5

	property real start: 0.0
	property real value: 0.0
	property string symbol: "M"
	property alias font: symbolText.font

	SymbolCanvas {
		id: canvas

		anchors.fill: parent

		element: root

		onPaint: {
			var ctx = getContext("2d")
			ctx.save()
			ctx.reset()

			ctx.lineWidth = units.strokeWidth
			ctx.fillStyle = color.background
			ctx.strokeStyle = color.stroke

			var r = (width - units.strokeWidth) * 0.5
			var xCenter = width * 0.5
			var yCenter = height * 0.5

			// Draw circle.
			ctx.beginPath()
			ctx.arc(xCenter, yCenter, r, 0, 2 * Math.PI)
			ctx.fill()
			ctx.stroke()

			// Draw progress
			ctx.beginPath()
			ctx.strokeStyle = color.background
			ctx.arc(xCenter, yCenter, r - units.strokeWidth, 0, 2 * Math.PI)
			ctx.stroke()

			ctx.beginPath()
			ctx.strokeStyle = color.foreground
			ctx.arc(xCenter, yCenter, r - units.strokeWidth, start * 2 * Math.PI - 0.5 * Math.PI, value * 2 * Math.PI - 0.5 * Math.PI)
			ctx.stroke()

			ctx.restore()
		}

		Connections {
			target: root

			function onStartChanged() {
				canvas.requestPaint()
			}

			function onValueChanged() {
				canvas.requestPaint()
			}
		}
	}

	Text {
		id: symbolText

		anchors.centerIn: parent
		color: root.color.foreground
		font.family: Theme.fonts.monospace.family
		font.pixelSize: units.quadrat * 0.2
		text: parent.symbol
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
