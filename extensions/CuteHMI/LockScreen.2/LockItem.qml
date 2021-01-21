import QtQuick 2.0
import QtQuick.Controls 2.1

import CuteHMI.LockScreen 2.0

Control {
	id: root

	padding: 0

	property PasswordInput passwordInput

	property var secret: new ArrayBuffer

	property Gatekeeper gatekeeper: Gatekeeper {
		password: root.passwordInput ? root.passwordInput.text : ""
		secret: root.secret
	}

	Binding {
		target: root.passwordInput
		property: "parent"
		value: root.contentItem
	}
}
