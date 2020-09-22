import QtQuick 2.0

import CuteHMI.GUI 1.0

import "functions.js" as Functions

/**
  Pipe.

  This component draws pipe between pipe connector @a from and pipe connector @a to. Pipe must have parent item.
  */
PipeElement {
	id: root

	transformOrigin: Item.Left

	property PipeConnector from

	property PipeConnector to

	Component.onCompleted: update()

	function update() {
		if (from !== undefined && to !== undefined) {
			var localFrom = from.mapToPipe(this, to)
			var localTo = to.mapToPipe(this, from)

			x = localFrom.x
			y = localFrom.y - diameter * 0.5

			implicitWidth = Functions.euclideanDistance(localTo, localFrom)

			rotation = Math.atan2(localTo.y - localFrom.y, localTo.x - localFrom.x) * 180 / Math.PI;

			implicitHeight = diameter

			canvas.requestPaint()
		}
	}

	Canvas {
		id: canvas

		antialiasing: true
		anchors.fill: parent

		onPaint: {
			var ctx = getContext('2d')
			ctx.save()
			ctx.reset()

			// Draw outerior
			ctx.lineWidth = root.diameter
			ctx.strokeStyle = createStyle(ctx, root.color.wall)
			ctx.moveTo(0, diameter * 0.5)
			ctx.lineTo(width, diameter * 0.5)
			ctx.stroke()

			// Draw interior
			ctx.lineWidth = root.diameter - root.thickness * 2.0
			ctx.strokeStyle = createStyle(ctx, root.color.interior)
			ctx.stroke()

			ctx.restore()
		}

		function createStyle(context, color) {
			if (Array.isArray(color)) {
				if (color.length <= 1)
					return color[0]
				var gradient = context.createLinearGradient(0, 0, width, 0);
				var offsetStep = 1.0 / (color.length - 1)
				var currentOffset = 0.0
				for (var i in color) {
					gradient.addColorStop(currentOffset, color[i])
					currentOffset += offsetStep
				}
				return gradient
			} else
				return color
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
