import QtQuick 2.5

Item
{
	id: root

	property real value: 0.0
	property int fractionalWidth: 1
	property int integralWidth: 3
	property alias font: unitDisplay.font
	property string unit: "°C"

	property alias border: background.border
	property alias color: background.color
	property alias stateColor: stateColor
	property alias radius: background.radius

	implicitWidth: background.width
	implicitHeight: background.height
	state: "normal"

	states: [
		State {
			name: "normal"

			// Scale is set explicitly, because even tho' "zoomed" state has "restoreEntryValues" set to true,
			// TextDisplay may not return to normal scale, when using animation. If TextDisplay is zoomed and rapid
			// click occurs, then if TextDisplay has not finished its zoomout animation yet, PropertyChanges will assume that
			// scale in the middle of animation is the one that should be restored. In short, rapid clicks on TextDisplay
			// might leave it permanently zoomed.
			// This may be a Qt bug, but not marking it as workaround for now as this may be correct "restoreEntryValues"
			// semantics as well (it restores properties to the actual values existing at the time of state change
			// rather than values from the previous state).
			PropertyChanges { target: root; scale: 1.0; color: stateColor.normal}
		},
		State {
			name: "zoomed"

			PropertyChanges { target: root; scale: 3.0}
		},
		State {
			name: "dirty"
			extend: "zoomed"

			StateChangeScript { script: dirtyTimeout.start() }
		},
		State {
			name: "disabled"

			PropertyChanges { target: root; color: stateColor.disabled}
		},
		State {
			name: "alert"

			PropertyChanges { target: root; color: stateColor.alert}
		}
	]

	Behavior on scale
	{
		NumberAnimation { duration: 100 }
	}

	Timer
	{
		id: dirtyTimeout

		interval: 800;
		onTriggered: root.state = "normal"
	}

	QtObject
	{
		id: stateColor

		property color normal: "#CCF4CC"
		property color disabled: "#E3E3E3"
		property color alert: "#FF3300"
	}

	QtObject
	{
		id: textFormatter

		property string textValue: root.value.toFixed(root.fractionalWidth)
	}

	Rectangle
	{
		id: background

		color: stateColor.normal
		border.width: height / 25.0
		radius: height / 5.0
		anchors.fill: textLayout
		anchors.margins: - root.font.pixelSize / 3
	}

	Row
	{
		id: textLayout

		spacing: root.font.pixelSize / 5
		anchors.centerIn: parent

		Text
		{
			id: valueDisplay

			font: unitDisplay.font
			text: textFormatter.textValue
			horizontalAlignment: Text.AlignRight
			width: Math.max(contentWidth, contentWidth / textFormatter.textValue.length * (root.fractionalWidth + root.integralWidth + 1))
		}

		Text
		{
			id: unitDisplay

			font.family: "Liberation Mono"
			font.pixelSize: 30
			text: root.unit
		}
	}

	MouseArea
	{
		id: rootArea

		anchors.fill: parent

		onPressed: root.state = "zoomed"
		onReleased: root.state = "dirty"
		onCanceled: root.state = "dirty"
	}

	onEnabledChanged: enabled ? root.state = "normal" : root.state = "disabled"
}
