import QtQuick 2.5
import QtQuick.Templates 2.0 as Templates

//<workaround id="QML_Base-4" target="Qt" cause="QTBUG-34418">
// Singletons require explicit import to load qmldir file.
import "."
//</workaround>

Templates.Control
{
	id: root

	implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
	implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding
	padding: font.pixelSize / 3

	property real value: 0.0
	property int fractionalWidth: 1
	property int integralWidth: 3
	property string unit: "°C"

	property var textFormatter: QtObject {
		property string valueText: root.value.toFixed(root.fractionalWidth)
	}

	background: Rectangle {
		color: Palette.background.normal
		border.width: height / 25.0
		radius: height / 5.0

		Behavior on color {
			ColorAnimation {}
		}
	}

	contentItem: Row {
		spacing: root.font.pixelSize / 5

		Text
		{
			id: valueDisplay

			font: root.font
			text: textFormatter.valueText
			horizontalAlignment: Text.AlignRight
			width: Math.max(contentWidth, contentWidth / textFormatter.valueText.length * (root.fractionalWidth + root.integralWidth + 1))
		}

		Text
		{
			id: unitDisplay

			font: root.font
			text: root.unit
		}
	}
}
