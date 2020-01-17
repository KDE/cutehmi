import QtQuick 2.5

import CuteHMI.GUI 0.0

Canvas {
	property Element element

	Connections {
		target: element.color

		onBaseChanged: requestPaint()
		onFillChanged: requestPaint()
		onTintChanged: requestPaint()
		onShadeChanged: requestPaint()
		onForegroundChanged: requestPaint()
		onBackgroundChanged: requestPaint()
		onStrokeChanged: requestPaint()
		onBlankChanged: requestPaint()
	}

	Connections {
		target: element

		onStrokeWidthChanged: requestPaint()
	}
}
