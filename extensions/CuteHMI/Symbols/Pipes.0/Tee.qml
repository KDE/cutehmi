import QtQuick 2.0

import CuteHMI.GUI 0.0

/**
  Tee pipe fitting.
  */
PipeElement {
	id: root

	implicitWidth: diameter
	implicitHeight: diameter

	property real length: diameter

	property ConnectorSelector connector: ConnectorSelector {
		parent: root
		connectors: [sideA, sideB, middle]

		property PipeConnector sideA: PipeConnector {
			x: -length
			y: diameter * 0.5
			parent: root
		}

		property PipeConnector sideB: PipeConnector {
			x: diameter + length
			y: diameter * 0.5
			parent: root
		}

		property PipeConnector middle: PipeConnector {
			x: width * 0.5
			y: diameter + length
			parent: root
		}
	}

	Canvas {
		x: -length
		implicitWidth: diameter + 2 * length
		implicitHeight: diameter + length

		antialiasing: true

		onPaint: {
			var ctx = getContext('2d')
			ctx.save()
			ctx.reset()

			// Draw outerior
			ctx.lineWidth = root.diameter
			ctx.strokeStyle = root.color.wall
			ctx.moveTo(0, diameter * 0.5)
			ctx.lineTo(width, diameter * 0.5)
			ctx.moveTo(width * 0.5, diameter * 0.5)
			ctx.lineTo(width * 0.5, height)
			ctx.stroke()

			// Draw interior
			ctx.lineWidth = root.diameter - root.thickness * 2.0
			ctx.strokeStyle = root.color.interior
			ctx.stroke()

			ctx.restore()
		}
	}
}
