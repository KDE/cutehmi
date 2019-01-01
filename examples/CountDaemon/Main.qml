import QtQuick 2.0

QtObject {
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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE, Version 1.
//(c)MP: DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//(c)MP: 0. You just DO WHAT THE FUCK YOU WANT TO.
//(c)MP: 1. NO FUCKING WARRANTY!
