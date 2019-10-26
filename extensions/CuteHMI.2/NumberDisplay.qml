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

//(c)MP: Copyright © 2018-2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
