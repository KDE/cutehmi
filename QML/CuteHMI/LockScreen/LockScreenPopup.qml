import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

import CuteHMI.LockScreen 1.0
import CuteHMI.App 1.0

Popup {
	id: lockScreenPopup

	z: Number.MAX_VALUE

	property Component lockScreenComponent

	padding: 0.0
	modal: true
	closePolicy: Popup.NoAutoClose

	contentItem: Loader {
		id: lockScreenLoader
		sourceComponent: lockScreenComponent

		Connections {
			target: lockScreenLoader.item
			onUnlocked: lockScreenPopup.close()
			onPasswordInputChanged: {
				if (lockScreenLoader.item.passwordInput.length === 0)
					passwordTimer.stop()
				else
					passwordTimer.restart()
			}
		}
	}

	enter: Transition {
		NumberAnimation {
			property: "opacity"
			from: 0.0
			to: 1.0
			duration: 750
		}
	}

	Connections {
		target: CuteApp
		onIdleChanged: {
			if (CuteApp.idle >= Settings.timeout && Settings.activated) {
				lockScreenPopup.open()
				Auth.locked = true
			}
		}
	}

	Timer {
		id: passwordTimer
		interval: 1000
		onTriggered: lockScreenLoader.item.tryUnlock()
	}

	Binding {
		target: CuteApp
		property: "idleMeasureEnabled"
		value: Settings.activated
	}
}

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
