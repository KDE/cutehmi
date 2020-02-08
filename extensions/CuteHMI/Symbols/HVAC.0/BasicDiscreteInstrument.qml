import QtQuick 2.0

import CuteHMI.GUI 0.0

/**
  Basic discrete instrument.
  */
Element {
	id: root

	implicitWidth: CuteApplication.theme.units.quadrat * 0.5
	implicitHeight: CuteApplication.theme.units.quadrat * 0.5
	active: true

	property string symbol: "TT"

	property alias font: symbolText.font

	Rectangle {
		anchors.fill: parent
		color: root.color.background
		border.color: root.color.stroke
		border.width: strokeWidth
		radius: height * 0.5
	}

	Text {
		id: symbolText

		anchors.centerIn: parent
		color: root.color.foreground
		font.family: CuteApplication.theme.fonts.monospace.family
		font.pixelSize: CuteApplication.theme.units.quadrat * 0.2
		text: parent.symbol
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
