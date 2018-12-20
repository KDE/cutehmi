import QtQuick 2.0

QtObject {
	property int test: 0

	Component.onCompleted: {
		console.log("Hello from counting daemon!")
	}

	property Timer timer: Timer {
		interval: 1000
		running: true
		repeat: true

		property int ctr: 0

		onTriggered: {
			ctr++;
			console.log("I can count to", ctr)
			if (ctr === 10)
				Qt.quit()
		}
	}
}
