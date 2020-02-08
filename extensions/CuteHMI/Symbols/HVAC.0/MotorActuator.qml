import QtQuick 2.0

import CuteHMI.GUI 0.0

/**
  Motor actuator.
  */
Element {
	id: root

	implicitWidth: CuteApplication.theme.units.quadrat * 0.5
	implicitHeight: CuteApplication.theme.units.quadrat * 0.5

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

			ctx.lineWidth = root.strokeWidth
			ctx.fillStyle = root.color.background
			ctx.strokeStyle = root.color.stroke

			var r = (width - strokeWidth) * 0.5
			var xCenter = width * 0.5
			var yCenter = height * 0.5

			// Draw cricle.
			ctx.beginPath()
			ctx.arc(xCenter, yCenter, r, 0, 2 * Math.PI)
			ctx.fill()
			ctx.stroke()

			// Draw progress
			ctx.beginPath()
			ctx.strokeStyle = root.color.background
			ctx.arc(xCenter, yCenter, r - strokeWidth, 0, 2 * Math.PI)
			ctx.stroke()

			ctx.beginPath()
			ctx.strokeStyle = root.color.foreground
			ctx.arc(xCenter, yCenter, r - strokeWidth, start * 2 * Math.PI - 0.5 * Math.PI, value * 2 * Math.PI - 0.5 * Math.PI)
			ctx.stroke()

			ctx.restore()
		}

		Connections {
			target: root

			onStartChanged: canvas.requestPaint()
			onValueChanged: canvas.requestPaint()
		}
	}

	Text {
		id: symbolText

		anchors.centerIn: parent
		color: root.color.foreground
		font.family: CuteApplication.theme.fonts.monospace.family
		font.pixelSize: CuteApplication.theme.units.quadrat * 0.2
		text: parent.symbol
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
