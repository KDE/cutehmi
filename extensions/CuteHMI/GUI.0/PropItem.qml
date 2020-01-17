import QtQuick 2.3

import CuteHMI.GUI 0.0

/**
  Prop item.

  This simple item can be used to draw small props around an actual item, which can be placed inside PropItem. Prop size
  can be controlled with padding properties (leftPadding, rightPadding, topPadding, bottomPadding).
  */
Canvas {
	id: root

	implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
	implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding

	/**
	  Prop thickness.
	  */
	property real thickness: 2.0

	/**
	  Prop color.
	  */
	property color color: CuteApplication.theme.palette.neutral.stroke

	/**
	  Left padding.
	  */
	property real leftPadding: 0.0

	/**
	  Right padding.
	  */
	property real rightPadding: 0.0

	/**
	  Top padding.
	  */
	property real topPadding: 0.0

	/**
	  Bottom padding.
	  */
	property real bottomPadding: 0.0

	/**
	  Content data.
	  */
	default property alias contentData: contentItem.data

	Item {
		id: contentItem

		x: leftPadding
		y: topPadding

		implicitWidth: childrenRect.width
		implicitHeight: childrenRect.height
	}

	onThicknessChanged: requestPaint()

	onColorChanged: requestPaint()

	onLeftPaddingChanged: requestPaint()

	onRightPaddingChanged: requestPaint()

	onTopPaddingChanged: requestPaint()

	onBottomPaddingChanged: requestPaint()

	onPaint: {
		var ctx = getContext('2d')
		ctx.save()
		ctx.reset()

		ctx.strokeStyle = color
		ctx.lineWidth = thickness

		var xCenter = leftPadding + contentItem.implicitWidth / 2.0
		var yCenter = topPadding + contentItem.implicitHeight / 2.0
		var offset = thickness * 0.5

		// Draw horizontal props(s).
		if (topPadding > 0.0 && bottomPadding > 0.0) {
			if (leftPadding > 0.0) {
				ctx.moveTo(0.0, offset)
				ctx.lineTo(xCenter, offset)
				ctx.moveTo(0.0, height - offset)
				ctx.lineTo(xCenter, height - offset)
			}
			if (rightPadding > 0.0) {
				ctx.moveTo(xCenter, offset)
				ctx.lineTo(width, offset)
				ctx.moveTo(xCenter, height - offset)
				ctx.lineTo(width, height - offset)
			}
		} else {
			ctx.moveTo(0.0, yCenter)
			ctx.lineTo(width, yCenter)
		}

		// Draw vertical prop(s).
		if (leftPadding > 0.0 && rightPadding > 0.0) {
			// Draw two side props.
			if (topPadding > 0.0) {
				ctx.moveTo(offset, 0.0)
				ctx.lineTo(offset, yCenter)
				ctx.moveTo(width - offset, 0.0)
				ctx.lineTo(width - offset, yCenter)
			}
			if (bottomPadding > 0.0) {
				ctx.moveTo(offset, yCenter)
				ctx.lineTo(offset, height)
				ctx.moveTo(width - offset, yCenter)
				ctx.lineTo(width - offset, height)
			}
		} else {
			// Draw single prop.
			ctx.moveTo(xCenter, 0.0)
			ctx.lineTo(xCenter, height)
		}
		ctx.stroke()

		ctx.restore();
	}

}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
