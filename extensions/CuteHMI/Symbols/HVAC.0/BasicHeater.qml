import QtQuick 2.0

HeatExchanger {
	id: root

	content: Component {
		SymbolCanvas {
			element: root

			onPaint: {
				var ctx = getContext("2d")
				ctx.save()
				ctx.reset()

				ctx.lineWidth = root.strokeWidth
				ctx.fillStyle = root.color.background
				ctx.strokeStyle = root.color.foreground

				// Draw plus symbol with radius r.
				var r = width * 0.25
				var xCenter = width * 0.5
				var yCenter = height * 0.5

				// Draw cricle.
				ctx.beginPath()
				ctx.arc(xCenter, yCenter, r, 0, 2 * Math.PI)
				ctx.fill()
				ctx.stroke()

				// Draw plus.
				ctx.beginPath()
				ctx.moveTo(xCenter - r * 0.5, yCenter)
				ctx.lineTo(xCenter + r * 0.5, yCenter)
				ctx.moveTo(xCenter, yCenter - r * 0.5)
				ctx.lineTo(xCenter, yCenter + r * 0.5)
				ctx.stroke()

				ctx.restore()
			}
		}
	}
}
