import QtQuick 2.0

import CuteHMI.GUI 0.0

Element
{
	id: root

	implicitWidth: CuteApplication.theme.units.quadrat * 1.25
	implicitHeight: CuteApplication.theme.units.quadrat

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
				ctx.lineWidth = strokeWidth

				var offset = strokeWidth * 0.5
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
				onDiameterChanged: requestPaint()
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
				ctx.lineWidth = strokeWidth

				// Draw fan wheel.
				var x = width * 0.5
				var y = height * 0.5
				var wheelR = wheelDiameter * 0.5

				ctx.arc(x, y, wheelR, 0.0, 2 * Math.PI, false)
				ctx.fill()
				ctx.stroke()

				// Draw bearings
				ctx.beginPath()
				ctx.arc(x, y, strokeWidth, 0.0, 2 * Math.PI, false)
				ctx.stroke()

				// Draw blades.
				var angle = Math.PI / 6.0
				var sinAngle = Math.sin(angle)
				var cosAngle = Math.cos(angle)
				var x1 = 0.0
				var y1 = strokeWidth
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
				onRpmChanged: handleRotation()

				Component.onCompleted: handleRotation()

				function handleRotation() {
					rotationAnimation.from = rotation % 360
					rotationAnimation.to = rotation % 360 + 360 * Math.ceil(root.rpm)
					if (root.rpm)
						rotationAnimation.restart()
					else
						rotationAnimation.stop()
				}
			}

			Connections {
				target: root.internal
				onWheelDiameterChanged: requestPaint()
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
