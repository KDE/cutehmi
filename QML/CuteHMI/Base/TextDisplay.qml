import QtQuick 2.5
//import pl.ekterm.libcutehmibase 1.0

Item {
	id: root
	property real value: 0.0
	property int fractionalWidth: 1
	property int integralWidth: 3
	property font font: Qt.font({family: "Lucida Console", pointSize: 20})
	property string unit: "°C"
//	property real source : aaa.x(integralWidth)
//	property int address
//	property TestItem

	width: background.width
	height: background.height

	QtObject {
		id: textFormatter
		property string textValue: root.value.toFixed(root.fractionalWidth)
	}

	Rectangle {
		id: background
		color: "lightgreen"
		border.width: 2
		radius: 10
		anchors.fill: textLayout
		anchors.margins: -10
	}

	Row {
		id: textLayout
		spacing: 5
		anchors.centerIn: parent

		Text {
			id: valueDisplay
			font: root.font
			text: textFormatter.textValue
			horizontalAlignment: Text.AlignRight
			width: Math.max(contentWidth, contentWidth / textFormatter.textValue.length * (root.fractionalWidth + root.integralWidth + 1))
		}

		Text {
			id: unitDisplay
			font: root.font
			text: root.unit
		}
	}

//	DevicePoint {
//		id: devicePoint
//		source: root.source
//	}
}
