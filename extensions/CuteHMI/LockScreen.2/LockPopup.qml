import QtQuick 2.0
import QtQuick.Controls 2.1

Popup {
	id: root

	padding: 0
	modal: true
	closePolicy: Popup.NoAutoClose

	property LockItem lockItem

	background: Rectangle {
		color: palette.shadow
	}

	onVisibleChanged: if (!enabled) close()

	Connections {
		target: root.lockItem.passwordInput

		onAccepted: if (root.lockItem.gatekeeper.authenticate()) root.close()
	}

	Binding {
		target: root.lockItem
		property: "parent"
		value: root.contentItem
	}
}
