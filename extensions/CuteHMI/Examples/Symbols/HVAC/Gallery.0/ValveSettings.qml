import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import CuteHMI.Symbols.HVAC 0.0

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
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
