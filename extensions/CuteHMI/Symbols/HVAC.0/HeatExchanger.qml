import QtQuick 2.0

import CuteHMI.GUI 0.0

Element
{
	id: root

	implicitWidth: CuteApplication.theme.units.quadrat
	implicitHeight: CuteApplication.theme.units.quadrat * 1.5

	property Component housing: Component {
		Rectangle {
			color: root.color.fill
			border.color: root.color.stroke
			border.width: root.strokeWidth
		}
	}

	property Component content: Component {
		SymbolCanvas {
			element: root

			onPaint: {
				var ctx = getContext("2d")
				ctx.save()
				ctx.reset()

				ctx.lineWidth = root.strokeWidth
				ctx.strokeStyle = root.color.stroke

				// Draw diagonal line.
				ctx.moveTo(0, height)
				ctx.lineTo(width, 0)
				ctx.stroke()

				ctx.restore()
			}
		}
	}

	function symbolPos() {
		var l = 0.5 * (width + height - Math.sqrt(width * width + height * height))
		return Qt.point(width - l, height - l)
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: housing
	}

	Loader {
		width: root.width
		height: root.height
		sourceComponent: content
	}
}
