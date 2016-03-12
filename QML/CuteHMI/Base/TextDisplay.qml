import QtQuick 2.5

// <workaround id="QML_Base-1" target="Qt" cause="bug">
// After setting environmental variable QT_QUICK_CONTROLS_STYLE=Flat as documentation suggests Qt desktop application does not use flat style properly,
// although no warnings are printed to the output (as they normally should, if style can not be loaded). It seems that explicit import overcomes this bug.
// [It may be that QT_QUICK_CONTROLS_STYLE is not doing regular import and it's not dealing with plugin library correctly.]
import QtQuick.Controls.Styles.Flat 1.0
import QtQuick.Extras 1.0	// To surpass "QtQuick.Extras.Private is not installed" ComboBox error, when using Flat style.
// </workaround>

Item {
	id: root
	property real value: 0.0
	property int fractionalWidth: 1
	property int integralWidth: 3
	property font font: Qt.font({family: "Lucida Console", pointSize: 20})
	property string unit: "°C"

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
}
