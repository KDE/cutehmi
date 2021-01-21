import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import CuteHMI.LockScreen 2.0

Item {
	id: root

	readonly property string initialState: lockItem.gatekeeper.secret.byteLength !== 0 ? "OLD_PASSWORD" : "NEW_PASSWORD"

	property LockItem lockItem

	property int spacing: 10

	property int padding: 10

	signal accepted()

	signal rejected()

	state: initialState

	states: [
		State {
			name: "OLD_PASSWORD"

			PropertyChanges {
				target: label
				text: qsTr('Please enter old password.')
			}
		},

		State {
			name: "NEW_PASSWORD"

			PropertyChanges {
				target: label
				text: qsTr('Please enter new password.')
			}
		},

		State {
			name: "RETYPE_PASSWORD"

			PropertyChanges {
				target: label
				text: qsTr('Please re-enter the passowrd.')
			}

			PropertyChanges {
				target: acceptButton
				text: qsTr('Apply')
			}
		}
	]

	ColumnLayout {
		anchors.fill: parent
		anchors.margins: root.padding

		spacing: root.spacing

		RowLayout {
			id: controlsLayout

			spacing: root.spacing

			Button {
				id: cancelButton

				Layout.alignment: Qt.AlignLeft

				text: qsTr("Cancel")

				onClicked: {
					lockItem.passwordInput.reset()
					root.state = root.initialState
					rejected()
				}
			}

			Frame {
				Layout.alignment: Qt.AlignHCenter
				Layout.fillWidth: true

				Label {
					id: label

					anchors.centerIn: parent
				}
			}

			Button {
				id: acceptButton

				Layout.alignment: Qt.AlignRight

				text: qsTr("Next")

				onClicked: lockItem.passwordInput.accept()
			}
		}

		Rectangle {
			id: lockItemPlaceholder

			Layout.fillWidth: true
			Layout.fillHeight: true

			color: palette.shadow
		}
	}

	Binding {
		target: root.lockItem
		property: "parent"
		value: lockItemPlaceholder
	}

	Connections {
		target: lockItem.passwordInput

		property string newPassword

		onAccepted: {
			if (root.state === "OLD_PASSWORD") {
				if (root.lockItem.gatekeeper.authenticate()) {
					root.state = "NEW_PASSWORD"
					root.lockItem.secret = ""
				}
			} else if (root.state === "NEW_PASSWORD") {
				newPassword = root.lockItem.passwordInput.text
				if (newPassword !== "")
					root.lockItem.secret = root.lockItem.gatekeeper.makeSecret(newPassword)
				root.lockItem.passwordInput.reset()
				root.state = "RETYPE_PASSWORD"
			} else if (root.state === "RETYPE_PASSWORD") {
				if (newPassword === root.lockItem.passwordInput.text)
					passwordChangedDialog.open()
				else {
					root.lockItem.secret = ""
					passwordMismatchDialog.open()
				}
				root.lockItem.passwordInput.reset()
			}
		}
	}

	Dialog {
		id: passwordChangedDialog

		anchors.centerIn: parent

		modal: true
		closePolicy: Popup.NoAutoClose
		title: qsTr("Password Change")
		standardButtons: Dialog.Ok

		onAccepted: {
			root.accepted()
			root.state = root.initialState
		}

		Label {
			anchors.centerIn: parent

			text: qsTr("Password has been successfully changed!")
		}
	}

	Dialog {
		id: passwordMismatchDialog

		anchors.centerIn: parent

		modal: true
		closePolicy: Popup.NoAutoClose
		title: qsTr("Password Change")
		standardButtons: Dialog.Ok

		onAccepted: root.state = "NEW_PASSWORD"

		Label {
			anchors.centerIn: parent

			text: qsTr('Passwords do not match. Please enter new password again.')
		}
	}
}

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
