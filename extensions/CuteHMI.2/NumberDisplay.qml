import QtQuick 2.5
import QtQuick.Templates 2.0 as Templates

//<CuteHMI-3.workaround target="Qt" cause="QTBUG-34418">
// Palette is a singleton.
// Singletons require explicit import to load qmldir file.
import "."
//</CuteHMI-3.workaround>

/**
  Number display.

  Number display can be used to conveniently display numerical values with corresponding units of measurement. Number display tries
  to keep constant width. If that's not possible it expands to fit the content.
  */
Element
{
	id: root

	implicitWidth: background.width - valueDisplay.overfull
	implicitHeight: background.height
	active: value === value		// NaN === NaN equals false, thus NaN value deactivates display.

	/**
	  Font. Font that is used by the display. It may be desirable to set some monospace font.
	  */
	property alias font: valueDisplay.font

	/**
	  Left padding.
	  */
	property real leftPadding: font.pixelSize * 0.25

	/**
	  Right padding.
	  */
	property real rightPadding: font.pixelSize * 0.25

	/**
	  Top padding.
	  */
	property real topPadding: font.pixelSize * 0.25

	/**
	  Bottom padding.
	  */
	property real bottomPadding: font.pixelSize * 0.25

	/**
	  Value.
	  */
	property real value: NaN

	/**
	  Fractional width.
	  */
	property int fractionalWidth: 1

	/**
	  Integral width.
	  */
	property int integralWidth: 3

	/**
	  Unit of measurment.
	  */
	property string unit: "°C"

	/**
	  Text formatter.
	  */
	property var textFormatter: function(value) { return value.toFixed(root.fractionalWidth) }

	Rectangle {
		id: background

		x: -0.5 * valueDisplay.overfull
		width: contentItem.width + leftPadding + rightPadding
		height: contentItem.height + topPadding + bottomPadding
		color: backgroundColor
		border.width: lineWidth
		radius: height / 5
	}

	Row {
		id: contentItem

		x: leftPadding - 0.5 * valueDisplay.overfull
		y: topPadding
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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
