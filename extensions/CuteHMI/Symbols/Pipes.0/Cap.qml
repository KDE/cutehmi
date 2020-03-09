import QtQuick 2.0

/**
  Pipe cap.
  */
PipeElement {
	id: root

	implicitWidth: length
	implicitHeight: diameter

	property real length: diameter

	property PipeConnector connector: PipeConnector {
		x: 0
		y: diameter * 0.5
		parent: root
	}

	Canvas {
		anchors.fill: parent

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
			ctx.stroke()

			// Draw interior
			ctx.beginPath()
			ctx.lineWidth = root.diameter - root.thickness * 2.0
			ctx.strokeStyle = root.color.interior
			ctx.moveTo(0, diameter * 0.5)
			ctx.lineTo(width - root.thickness, diameter * 0.5)
			ctx.stroke()

			ctx.restore()
		}
	}
}
