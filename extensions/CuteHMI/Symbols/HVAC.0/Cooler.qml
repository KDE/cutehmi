import QtQuick 2.0

HeatExchanger {
	id: root

	content: Component {
		SymbolCanvas {
			property point symbolPos: root.symbolPos()

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

				// Draw diagonal line.
				ctx.moveTo(0, height)
				ctx.lineTo(width, 0)
				ctx.stroke()

				// Draw cricle.
				ctx.beginPath()
				ctx.arc(symbolPos.x, symbolPos.y, r, 0, 2 * Math.PI)
				ctx.fill()
				ctx.stroke()

				// Draw minus.
				ctx.beginPath()
				ctx.moveTo(symbolPos.x - r * 0.5, symbolPos.y)
				ctx.lineTo(symbolPos.x + r * 0.5, symbolPos.y)
				ctx.stroke()

				ctx.restore()
			}

			onSymbolPosChanged: requestPaint()
		}
	}
}
