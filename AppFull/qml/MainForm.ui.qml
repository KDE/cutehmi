import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

import CuteHMI 1.0

Item {
	width: 640
	height: 480

	Item {
		id: item1
		x: 24
		y: 24
		width: 200
		height: 200

		Rectangle {
			id: rectangle1
			x: 8
			y: 8
			width: 184
			height: 184
			color: "#7ce882"
			radius: 10
			visible: true
			clip: false
			border.width: 1
		}

		Text {
			id: text1
			x: 78
			y: 86
			text: qsTr("Text")
			font.pixelSize: 24
		}
	}

	Slider {
		id: slider1
		x: 346
		y: 29
		stepSize: 0.1
//		value: mb.r[1].int16
		value: 0.0
		maximumValue: 1000
		orientation: Qt.Vertical

//		onValueChanged: {
//			mb.r[1].int16 = value;
//		}

	}

 TextDisplay {
	 id: textDisplay1
	 x: 446
	 y: 24
	 width: 88
	 height: 40
	 value: slider1.value
 }

 TextDisplay {
	 id: textDisplay2
	 x: 65
	 y: 279
	 width: 119
	 height: 49
	 value: mb.r[1].int16
 }

 HMISlider {
	 id: hMISlider1
	 x: 257
	 y: 293
	 maximumValue: 100
	 bindingTarget: mb.r[1]

	 Component.onCompleted: {
			bindingTarget.valueChanged.connect(updateValue)
	 }

	 function updateValue() {
		 if (value !== mb.r[1].int16)
			value = mb.r[1].int16
	 }
 }

}
