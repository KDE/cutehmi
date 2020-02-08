import QtQuick 2.0

import CuteHMI.GUI 0.0

/**
  Heat exchanger.
  */
Element {
	id: root

	implicitWidth: CuteApplication.theme.units.quadrat
	implicitHeight: CuteApplication.theme.units.quadrat * 1.5
	active: true

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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
