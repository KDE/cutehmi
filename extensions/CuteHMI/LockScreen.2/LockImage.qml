import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.LockScreen 2.0

LockItem {
	id: root

	background: backgroundImage

	contentItem: Item {
		transform: [
			Scale {
				xScale: root.backgroundImage.paintedWidth / root.backgroundImage.sourceSize.width
				yScale: root.backgroundImage.paintedHeight / root.backgroundImage.sourceSize.height
			},

			Translate {
				x: (root.backgroundImage.width - root.backgroundImage.paintedWidth) * 0.5
				y: (root.backgroundImage.height - root.backgroundImage.paintedHeight) * 0.5
			}
		]
	}

	property Image backgroundImage: Image {
		fillMode: Image.PreserveAspectFit
	}

	property Animation wrongPasswordAnimation: SequentialAnimation {
		loops: 4

		property int duration: 10

		property real amplitude: 10.0

		NumberAnimation {
			target: root.background
			property: "x"
			from: 0
			to: root.wrongPasswordAnimation.amplitude
			duration: root.wrongPasswordAnimation.duration
		}

		NumberAnimation {
			target: root.background
			property: "x"
			from: root.wrongPasswordAnimation.amplitude
			to: -root.wrongPasswordAnimation.amplitude
			duration: 2 * root.wrongPasswordAnimation.duration
		}

		NumberAnimation {
			target: root.background
			property: "x"
			from: -root.wrongPasswordAnimation.amplitude
			to: 0
			duration: root.wrongPasswordAnimation.duration
		}
	}

	Binding {
		target: root.passwordInput
		property: "width"
		value: root.backgroundImage.sourceSize.width
	}

	Binding {
		target: root.passwordInput
		property: "height"
		value: root.backgroundImage.sourceSize.height
	}

	Connections {
		target: root.passwordInput

		function onAccepted() {
			if (!root.gatekeeper.authenticate())
				root.wrongPasswordAnimation.restart()
		}
	}
}

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
