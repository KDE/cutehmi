import QtQuick 2.0

import CuteHMI.LockScreen 2.0

LockImage {
	backgroundImage.source: Qt.resolvedUrl("images/christmas.jpg")

	passwordInput: Keypad {
		HiddenButton {
			x: 90
			y: 795
			implicitWidth: 300
			implicitHeight: 300

			text: "0"

			radius: width * 0.5
		}

		HiddenButton {
			x: 338
			y: 553
			implicitWidth: 440
			implicitHeight: 440

			text: "1"

			radius: width * 0.5
		}

		HiddenButton {
			x: 955
			y: 445
			implicitWidth: 455
			implicitHeight: 455

			text: "2"

			radius: width * 0.5
		}
	}
}
