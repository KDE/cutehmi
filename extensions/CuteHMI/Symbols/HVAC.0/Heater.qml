import QtQuick 2.0

/**
  Heater.
  */
HeatExchanger {
	id: root

	content: Component {
		SymbolCanvas {
			element: root

			property point symbolPos: root.symbolPos()

			onPaint: {
				var ctx = getContext("2d")
				ctx.save()
				ctx.reset()

				ctx.lineWidth = root.units.strokeWidth
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

				// Draw plus.
				ctx.beginPath()
				ctx.moveTo(symbolPos.x - r * 0.5, symbolPos.y)
				ctx.lineTo(symbolPos.x + r * 0.5, symbolPos.y)
				ctx.moveTo(symbolPos.x, symbolPos.y - r * 0.5)
				ctx.lineTo(symbolPos.x, symbolPos.y + r * 0.5)
				ctx.stroke()

				ctx.restore()
			}

			onSymbolPosChanged: requestPaint()
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
