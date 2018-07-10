import QtQuick 2.5
import QtQuick.Templates 2.0 as Templates

//<workaround id="cutehmi_1_qml-4" target="Qt" cause="QTBUG-34418">
// Palette is a singleton.
// Singletons require explicit import to load qmldir file.
import "."
//</workaround>

Element
{
	id: root

	implicitWidth: background.width - valueDisplay.overfull
	implicitHeight: background.height
	active: value === value		// NaN === NaN equals false, thus NaN value deactivates display.

	property alias font: valueDisplay.font
	property real paddingLeft: font.pixelSize * 0.25
	property real paddingRight: font.pixelSize * 0.25
	property real paddingTop: font.pixelSize * 0.25
	property real paddingBottom: font.pixelSize * 0.25
	property real value: NaN
	property int fractionalWidth: 1
	property int integralWidth: 3
	property string unit: "Â°C"

	property var textFormatter: function(value) { return value.toFixed(root.fractionalWidth) }

	Rectangle {
		id: background

		x: -0.5 * valueDisplay.overfull
		width: contentItem.width + paddingLeft + paddingRight
		height: contentItem.height + paddingTop + paddingBottom
		color: backgroundColor
		border.width: lineWidth
		radius: height / 5
	}

	Row {
		id: contentItem

		x: paddingLeft - 0.5 * valueDisplay.overfull
		y: paddingTop
		spacing: root.font.pixelSize * 0.25

		Text
		{
			id: valueDisplay

			color: foregroundColor
			text: textFormatter(root.value)
			horizontalAlignment: Text.AlignRight
			width: Math.max(contentWidth, nominaLWidth)

			property real overfull: width - nominaLWidth
			property real nominaLWidth: contentWidth / text.length * (root.fractionalWidth + root.integralWidth + 1)
		}

		Text
		{
			id: unitDisplay

			font: root.font
			color: foregroundColor
			text: root.unit
		}
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
