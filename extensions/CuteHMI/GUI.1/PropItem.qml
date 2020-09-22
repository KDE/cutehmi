import QtQuick 2.3

import CuteHMI.GUI 1.0

/**
  Prop item.

  This simple item can be used to draw small props around an actual item, which can be placed inside PropItem. Prop size
  can be controlled with padding properties (@a leftPadding, @a rightPadding, @a topPadding, @a bottomPadding).

  ![Prop item preview](doc/PropItem_preview.png)

  Above image has been obtained with the following sample code demonstrating basic use of prop item.

  @snippet tests/tst_PropItem.qml PropItem preview
  */
Canvas {
	id: root

	implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
	implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding

	/**
	  Prop thickness.
	  */
	property real thickness: Theme.units.strokeWidth

	/**
	  Prop color.
	  */
	property color color: Theme.palette.neutral.stroke

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
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
