import QtQuick 2.3

//<CuteHMI-3.workaround target="Qt" cause="QTBUG-34418">
// Palette is a singleton.
// Singletons require explicit import to load qmldir file.
import "."
//</CuteHMI-3.workaround>

Canvas {
	id: root

	implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
	implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding

	property real thickness: 2.0
	property color color: Palette.neutral.stroke

	property real leftPadding: 0.0
	property real rightPadding: 0.0
	property real topPadding: 0.0
	property real bottomPadding: 0.0

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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
