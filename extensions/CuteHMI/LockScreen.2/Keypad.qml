import QtQml 2.12
import QtQuick 2.0
import QtQuick.Controls 2.12

PasswordInput {
	id: root

	contentItem: Item {}

	property int typingTimeout: 1000

	property string enteredText: ""

	function reset() {
		text = ""
		enteredText = ""
	}

	function accept() {
		text = enteredText
		enteredText = ""
		accepted()
	}

	// Similar functionality could be also implemented with ButtonGroup, but Connections give a bit more flexibility.
	Instantiator {
		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="bug">
		// For some reason specifying contentModel alone does not create instances, even though `count` property shows correct value.
		model: contentModel.count
		//</CuteHMI.LockScreen-1.workaround>

		Connections {
			target: contentModel.get(index)
			ignoreUnknownSignals: true

			onClicked: {
				root.setCurrentIndex(index)
				root.enteredText += contentModel.get(index).text
				if (autoAccept)
					typingTimeoutTimer.restart()
			}
		}
	}

	Instantiator {
		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="bug">
		// For some reason specifying contentModel alone does not create instances, even though `count` property shows correct value.
		model: contentModel.count
		//</CuteHMI.LockScreen-1.workaround>

		Binding {
			target: contentModel.get(index)
			property: "down"
			value: contentModel.get(index).pressed ^ !root.discretion
		}
	}

	Timer {
		id: typingTimeoutTimer

		interval: root.typingTimeout

		onTriggered: accept()
	}
}
