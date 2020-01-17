import QtQuick 2.0

import CuteHMI.GUI 0.0

Element {
	id: root

	implicitWidth: CuteApplication.theme.units.quadrat * 0.5
	implicitHeight: CuteApplication.theme.units.quadrat * 0.5

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
