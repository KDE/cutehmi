import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import CuteHMI.Symbols.HVAC 1.0

ElementSettings {
	element: valve

	property Valve valve

	GroupBox {
		title: qsTr("Custom properties")

		Layout.fillWidth: true

		GridLayout {
			columns: 2

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Left way:")
			}

			CheckBox {
				checked: valve.leftWay

				onCheckedChanged: valve.leftWay = checked
			}


			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Right way:")
			}

			CheckBox {
				checked: valve.rightWay

				onCheckedChanged: valve.rightWay = checked
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Top way:")
			}

			CheckBox {
				checked: valve.topWay

				onCheckedChanged: valve.topWay = checked
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Bottom way:")
			}

			CheckBox {
				checked: valve.bottomWay

				onCheckedChanged: valve.bottomWay = checked
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Left closed:")
			}

			CheckBox {
				checked: valve.leftClosed

				onCheckedChanged: valve.leftClosed = checked
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Right closed:")
			}

			CheckBox {
				checked: valve.rightClosed

				onCheckedChanged: valve.rightClosed = checked
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Top closed:")
			}

			CheckBox {
				checked: valve.topClosed

				onCheckedChanged: valve.topClosed = checked
			}

			Label {
				Layout.alignment: Qt.AlignRight

				text: qsTr("Bottom closed:")
			}

			CheckBox {
				checked: valve.bottomClosed

				onCheckedChanged: valve.bottomClosed = checked
			}
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
