import QtQuick 2.5

import CuteHMI.GUI 1.0

/**
  Valve.
  */
Element {
	id: root

	implicitWidth: loaderWrapper.childrenRect.width
	implicitHeight: loaderWrapper.childrenRect.height

	active: true

	readonly property real wayWidth: units.quadrat * 0.25

	readonly property real wayHeight: units.quadrat * 0.25

	property bool leftWay: true

	property bool rightWay: true

	property bool topWay: false

	property bool bottomWay: false

	property bool leftClosed: false

	property bool rightClosed: false

	property bool topClosed: false

	property bool bottomClosed: false

	property Component way: Component {
		SymbolCanvas {
			id: canvas

			implicitWidth: root.wayWidth
			implicitHeight: root.wayHeight

			element: root

			onPaint: {
				var ctx = getContext('2d')
				ctx.save()
				ctx.reset()

				ctx.strokeStyle = root.color.stroke
				if (closed)
					ctx.fillStyle = root.color.stroke
				else
					ctx.fillStyle = root.color.fill
				ctx.lineWidth = units.strokeWidth

				var offset = units.strokeWidth / 2.0

				ctx.moveTo(offset, offset)
				ctx.lineTo(width - offset, height * 0.5)
				ctx.lineTo(offset, height - offset)
				ctx.closePath()
				ctx.fill()
				ctx.stroke()

				ctx.restore()
			}

			Connections {
				target: parent
				onClosedChanged: requestPaint()
			}
		}
	}

	Item {
		id: loaderWrapper

		Loader {
			y: topWay ? 0.5 * height : 0
			width: leftWay ? wayWidth : 0
			height: leftWay ? wayHeight : 0
			sourceComponent: leftWay ? way : undefined

			property bool closed: leftClosed
		}

		Loader {
			x: leftWay ? width : (topWay || bottomWay) ? width * 0.5 : 0
			y: topWay ? 0.5 * height : 0
			width: rightWay ? wayWidth : 0
			height: rightWay ? wayHeight : 0
			rotation: 180
			sourceComponent: rightWay ? way : undefined

			property bool closed: rightClosed
		}

		Loader {
			x: leftWay ? width * 0.5 : 0
			width: topWay ? wayWidth : 0
			height: topWay ? wayHeight : 0
			rotation: 90
			sourceComponent: topWay ? way : undefined

			property bool closed: topClosed
		}

		Loader {
			x: leftWay ? width * 0.5 : 0
			y: topWay ? height : (leftWay || rightWay) ? height * 0.5 : 0
			width: bottomWay ? wayWidth : 0
			height: bottomWay ? wayHeight : 0
			rotation: -90
			sourceComponent: bottomWay ? way : undefined

			property bool closed: bottomClosed
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
