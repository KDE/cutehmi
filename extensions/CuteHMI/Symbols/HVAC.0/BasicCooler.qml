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

				// Draw minus symbol with radius r.
				var r = width * 0.25
				var xCenter = width * 0.5
				var yCenter = height * 0.5

				// Draw circle.
				ctx.beginPath()
				ctx.arc(xCenter, yCenter, r, 0, 2 * Math.PI)
				ctx.fill()
				ctx.stroke()

				// Draw minus.
				ctx.beginPath()
				ctx.moveTo(xCenter - r * 0.5, yCenter)
				ctx.lineTo(xCenter + r * 0.5, yCenter)
				ctx.stroke()

				ctx.restore()
			}
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
