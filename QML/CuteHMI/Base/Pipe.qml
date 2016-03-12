import QtQuick 2.0
import QtQuick.Particles 2.0

Item {
	id: container

	width: size.width
	height: size.height

	property size size: findSize()
	property list<PipePoint> points	///< List of joint points (list<PipePoint>).
	property var paths	///< List of lists of paths (list<list<int>>). Each path refers to points in the @a points list and contains a list of indices to connect.
	property real velocityMagnitude: 0.0	///< Velocity of particles [pixels/s].
	property PipeEmitterSettings emitter: PipeEmitterSettings {}
	property ParticleSystem particleSystem

	property alias thickness: canvas.thickness
	property alias diameter: canvas.diameter
	property alias innerColor: canvas.innerColor
	property alias outerColor: canvas.outerColor
	property alias joinStyle: canvas.joinStyle
	property alias alpha: canvas.alpha

	Component {
		id: emitterComponent

		Emitter {
			width: emitter.width
			height: emitter.height
			emitRate: emitter.emitRate
			size: emitter.size
			velocity: PointDirection { x: 0; y: 0 }
		}
	}

	Component.onCompleted: {
		if (particleSystem == undefined)
			return
		for (var pathNum = 0; pathNum < paths.length; pathNum++) {
			var path = paths[pathNum]
			for (var i = 0; i < path.length - 1; i++) {
				var e = emitterComponent.createObject(container)
				e.x = points[path[i]].x - e.width / 2;
				e.y = points[path[i]].y - e.height / 2;
				var segmentVector = Qt.vector2d(points[path[i + 1]].x - points[path[i]].x, points[path[i + 1]].y - points[path[i]].y);
				var segmentVelocity = segmentVector.normalized().times(velocityMagnitude)
				e.velocity.x = segmentVelocity.x
				e.velocity.y = segmentVelocity.y
				var timeSpan = segmentVector.length() / velocityMagnitude * 1000.0	// length [pixels] / velocity [pixels/s] * 1000 [ms]
				e.lifeSpan = timeSpan
				e.startTime = timeSpan
				e.system =  particleSystem
			}
		}
	}

	Canvas {
		id: canvas
		width: container.width
		height: container.height
		antialiasing: true

		property real thickness: 5.0
		property real diameter: 40.0
		property color innerColor: "darkred"
		property color outerColor: "black"
		property string joinStyle: "miter"
		property real alpha: 1.0

		onPaint: {
			var ctx = canvas.getContext('2d');
			ctx.save();
			ctx.globalAlpha = canvas.alpha;
			ctx.lineJoin = canvas.joinStyle

			// Draw outerior
			ctx.strokeStyle = canvas.outerColor;
			ctx.lineWidth = canvas.diameter;
			for (var pathNum = 0; pathNum < paths.length; pathNum++) {
				var path = paths[pathNum]
				ctx.beginPath();
				ctx.moveTo(points[path[0]].x, points[path[0]].y)
				for (var i = 1; i < path.length; i++)
					ctx.lineTo(points[path[i]].x, points[path[i]].y)
				ctx.stroke();
			}

			// Draw interior
			ctx.strokeStyle = canvas.innerColor;
			ctx.lineWidth = canvas.diameter - canvas.thickness * 2.0;
			for (pathNum = 0; pathNum < paths.length; pathNum++) {
				path = paths[pathNum];
				ctx.beginPath();
				ctx.moveTo(points[path[0]].x, points[path[0]].y)
				for (i = 1; i < path.length; i++)
					ctx.lineTo(points[path[i]].x, points[path[i]].y)
				ctx.stroke();
			}

			ctx.restore();
		}
	}

	function findSize()
	{
		if (points.length === 0)
			return Qt.size(0.0, 0.0)
		var maxX = points[0].x
		var maxY = points[0].y
		for (var i = 1; i < points.length; i++) {
			maxX = Math.max(points[i].x, maxX)
			maxY = Math.max(points[i].y, maxY)
		}
		return Qt.size(Math.ceil(maxX + diameter / 2.0), Math.ceil(maxY + diameter / 2.0))
	}
}
