import QtQuick 2.5

/**
  @todo blinking text instead of washed out colour on "busy" state.

  @todo decrement z when display is really zoomed out (after scale animation finishes; currently z is decremented when state changes).
  */
Item
{
	id: root

	property real value: 0.0
	property int fractionalWidth: 1
	property int integralWidth: 3
	property alias font: unitDisplay.font
	property string unit: "°C"
	property bool zoom: false
	property int zZoomInc: 1	///< Denotes how much to increment z value on zoom in.

	property alias border: background.border
	property alias color: background.color
	property alias stateColor: stateColor
	property alias valueColor: valueDisplay.color
	property alias unitColor: unitDisplay.color
	property alias radius: background.radius

	implicitWidth: background.width
	implicitHeight: background.height
	state: "normal"

	states: [
		State {
			name: "normal"

			PropertyChanges { target: root; color: stateColor.normal; valueColor: stateColor.normalText}
		},
		State {
			name: "busy"

			PropertyChanges { target: root; color: root.color; valueColor: stateColor.busyText; unitColor: stateColor.normalText}
		},
		State {
			name: "zoomed"

			PropertyChanges { target: root; zoom: true; color: root.color; valueColor: root.valueColor; unitColor: root.unitColor}
		},
		State {
			name: "dirty"
			extend: "zoomed"

			StateChangeScript { script: dirtyTimeout.start() }
		},
		State {
			name: "disabled"

			PropertyChanges { target: root; color: stateColor.disabled; valueColor: stateColor.disabledText; unitColor: stateColor.disabledText}
		},
		State {
			name: "alert"

			PropertyChanges { target: root; color: stateColor.alert; valueColor: stateColor.alertText; unitColor: stateColor.normalText}
		}
	]

	property string _preZoomedState

	onStateChanged: {
		if ((state !== "zoomed") && (state !== "dirty"))
			_preZoomedState = state
	}

	onZoomChanged: {
		if (zoom) {
			scale = 3.0
			z += zZoomInc
		} else {
			scale = 1.0
			z -= zZoomInc
		}
	}

	Behavior on scale
	{
		NumberAnimation	{ duration: 100 }
	}

	Timer
	{
		id: dirtyTimeout

		interval: 800;
		onTriggered: root.state = _preZoomedState
	}

	QtObject
	{
		id: stateColor

		property color normal: "#CCF4CC"
		property color disabled: "#E3E3E3"
		property color alert: "#FF3300"
		property color normalText: "#000000"
		property color busyText: "#CCCCCC"
		property color disabledText: "#8E8E8E"
		property color alertText: "#000000"
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
