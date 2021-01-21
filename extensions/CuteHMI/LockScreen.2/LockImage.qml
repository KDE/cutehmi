import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.LockScreen 2.0

LockItem {
	id: root

	background: backgroundImage

	contentItem: Item {
		transform: [
			Scale {
				xScale: root.backgroundImage.paintedWidth / root.backgroundImage.sourceSize.width
				yScale: root.backgroundImage.paintedHeight / root.backgroundImage.sourceSize.height
			},

			Translate {
				x: (root.backgroundImage.width - root.backgroundImage.paintedWidth) * 0.5
				y: (root.backgroundImage.height - root.backgroundImage.paintedHeight) * 0.5
			}
		]
	}

	property Image backgroundImage: Image {
		fillMode: Image.PreserveAspectFit
	}

	property Animation wrongPasswordAnimation: SequentialAnimation {
		loops: 4

		property int duration: 10

		property real amplitude: 10.0

		NumberAnimation {
			target: root.background
			property: "x"
			from: 0
			to: root.wrongPasswordAnimation.amplitude
			duration: root.wrongPasswordAnimation.duration
		}

		NumberAnimation {
			target: root.background
			property: "x"
			from: root.wrongPasswordAnimation.amplitude
			to: -root.wrongPasswordAnimation.amplitude
			duration: 2 * root.wrongPasswordAnimation.duration
		}

		NumberAnimation {
			target: root.background
			property: "x"
			from: -root.wrongPasswordAnimation.amplitude
			to: 0
			duration: root.wrongPasswordAnimation.duration
		}
	}

	Binding {
		target: root.passwordInput
		property: "width"
		value: root.backgroundImage.sourceSize.width
	}

	Binding {
		target: root.passwordInput
		property: "height"
		value: root.backgroundImage.sourceSize.height
	}

	Connections {
		target: root.passwordInput

		onAccepted: if (!root.gatekeeper.authenticate()) root.wrongPasswordAnimation.restart()
	}
}
