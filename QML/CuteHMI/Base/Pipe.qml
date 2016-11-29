import QtQuick 2.0
import QtQuick.Particles 2.0

/**
  Pipe. By default pipe does not clip its contents.

  @todo use affectors to control velocity of particles.
  */
Item {
	id: container

	implicitWidth: size.width
	implicitHeight: size.height

	readonly property size size: findSize()	///< @todo recalculate when points are changed.

	property list<PipePoint> points	///< List of joint points (list<PipePoint>).
	property var paths	///< List of lists of paths (list<list<int>>). Each path refers to points in the @a points list and contains a list of indices to connect.
	property real velocityMagnitude: 0.0	///< Velocity of particles [pixels/s].
	property real velocityFactor: 1.0
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
			id: emitterInstance

			width: emitter.width
			height: emitter.height
			emitRate: emitter.emitRate
			size: emitter.size
			enabled: emitter.enabled
			velocity: PointDirection { x: 0; y: 0 }
			property real velocityFactor: container.velocityFactor
			property vector2d emissionVector;

			//<workaround id="QML_Base-2" target="Qt" cause="bug">
			// Particles emitted from the past are not rotated correctly with "autoRotate", so we will rotate them manually.

			//<workaround id="QML_Base-3" target="Qt" cause="bug">
			// Need to use Connections, because emitParticles.connect(onEmitParticlesOnce) sends QVariant(QQmlV4Handle) instead of
			// Array to the onEmitParticlesOnce(). Setting "target" here has a weird property (bug? Sth related to Javascript prototyping?)
			// that old emitters, which already have "target" set to null and are going to die, will be reconnected to onEmitParticlesOnce().
			Connections
			{
				id: onEmitParticlesWorkaround

				target: emitterInstance
				onEmitParticles: onEmitParticlesOnce(particles)
			}
			//</workaround>

			onVelocityFactorChanged: recalculateEmission()

			function onEmitParticlesOnce(particles)
			{
				// Rotate each particle according to its velocity vector.
				for (var i = 0; i < particles.length; i++) {
					particles[i].autoRotate = false
					particles[i].rotation = Math.atan2(particles[i].vy, particles[i].vx)
				}
				//<workaround id="QML_Base-3" target="Qt" cause="bug">
				onEmitParticlesWorkaround.target = null	// Disconnect from signal to not affect performance any more.
				//</workaround>
			}
			// </workaround>

			function recalculateEmission()
			{
				var resultingVelocity = velocityMagnitude * velocityFactor
				var velocityVector = emissionVector.normalized().times(resultingVelocity)
				velocity.x = velocityVector.x
				velocity.y = velocityVector.y
				if (velocityFactor > 0.01) {
					lifeSpan = emissionVector.length() / resultingVelocity * 1000.0	// length [pixels] / velocity [pixels/s] * 1000 [ms]
					emitRate = emitter.emitRate * velocityFactor
				} else
					emitRate = 0
			}
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
				e.emissionVector = Qt.vector2d(points[path[i + 1]].x - points[path[i]].x, points[path[i + 1]].y - points[path[i]].y);
				e.recalculateEmission()
				e.startTime = e.lifeSpan
				e.system =  particleSystem
			}
		}
	}

	Canvas {
		id: canvas

		x: boundingRect.x
		y: boundingRect.y
		width: boundingRect.width
		height: boundingRect.height
		antialiasing: true

		readonly property rect boundingRect: findBoundingRect() ///< @todo recalculate when points are changed.

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
				ctx.moveTo(points[path[0]].x - canvas.x, points[path[0]].y - canvas.y)
				for (var i = 1; i < path.length; i++)
					ctx.lineTo(points[path[i]].x - canvas.x, points[path[i]].y - canvas.y)
				ctx.stroke();
			}

			// Draw interior
			ctx.strokeStyle = canvas.innerColor;
			ctx.lineWidth = canvas.diameter - canvas.thickness * 2.0;
			for (pathNum = 0; pathNum < paths.length; pathNum++) {
				path = paths[pathNum];
				ctx.beginPath();
				ctx.moveTo(points[path[0]].x - canvas.x, points[path[0]].y - canvas.y)
				for (i = 1; i < path.length; i++)
					ctx.lineTo(points[path[i]].x - canvas.x, points[path[i]].y - canvas.y)
				ctx.stroke();
			}

			ctx.restore();
		}

		function findBoundingRect()
		{
			if (points.length === 0)
				return Qt.rect(0.0, 0.0, 0.0, 0.0)
			var minX = points[0].x
			var minY = points[0].y
			var maxX = points[0].x
			var maxY = points[0].y
			for (var i = 1; i < points.length; i++) {
				minX = Math.min(points[i].x, minX)
				minY = Math.min(points[i].y, minY)
				maxX = Math.max(points[i].x, maxX)
				maxY = Math.max(points[i].y, maxY)
			}
			var margin = diameter / 2.0
			return Qt.rect(Math.floor(minX - margin), Math.floor(minY - margin), Math.ceil(maxX - minX + diameter), Math.ceil(maxY - minY + diameter))
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
		var margin = diameter / 2.0
		return Qt.size(Math.ceil(maxX + margin), Math.ceil(maxY + margin))
	}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
