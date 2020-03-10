import QtQuick 2.0

/**
  Pipe end.
  */
PipeElement {
	id: root

	implicitWidth: length
	implicitHeight: diameter

	property real length: diameter

	property ConnectorSelector connector: ConnectorSelector {
		parent: root
		connectors: [sideA, sideB]

		property PipeConnector sideA: PipeConnector {
			x: 0
			y: diameter * 0.5
			parent: root
		}

		property PipeConnector sideB: PipeConnector {
			x: width
			y: diameter * 0.5
			parent: root
		}
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
			ctx.lineWidth = root.diameter - root.thickness * 2.0
			ctx.strokeStyle = root.color.interior
			ctx.stroke()

			ctx.restore()
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
