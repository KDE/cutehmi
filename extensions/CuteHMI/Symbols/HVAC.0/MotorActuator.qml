import QtQuick 2.0

import CuteHMI.GUI 0.0

Element
{
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
