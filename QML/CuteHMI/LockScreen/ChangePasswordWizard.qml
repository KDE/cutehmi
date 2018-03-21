import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import CuteHMI.LockScreen 1.0

Item {
	id: root
	property string newPassword
	property string retypedNewPassword
	property alias cancelButton: cancelButton
	property alias applyButton: applyButton
	property alias lockScreen: lockScreenLoader.item
	property Component lockScreenComponent
	signal finished

	states: [
		State {
			name: "NewPassword"
			PropertyChanges {
				target: label
				text: qsTr('Proszę wprowadzić nowe hasło, a następnie nacisnąć przycisk "Dalej"')
			}

			PropertyChanges {
				target: nextButton
				enabled: Auth.validatePassword(lockScreen.passwordInput)
			}

			PropertyChanges {
				target: lockScreen
				inverted: true
			}

			PropertyChanges {
				target: lockScreenConnection
				enabled: false
			}
		},
		State {
			name: "MismatchPassword"
			extend: "NewPassword"

			//			PropertyChanges {
			//				target: label
			//				text: qsTr('Hasła się nie zgadzają. Proszę wprowadzić nowe hasło, następnie przycisnąć "Dalej"')
			//			}
			PropertyChanges {
				target: mismatchPasswordDialog
				visible: true
			}
		},
		State {
			name: "RetypePassword"

			PropertyChanges {
				target: label
				text: qsTr('Proszę powtórzyć nowe hasło, a następnie nacisnąć przycisk "Zatwierdź"')
			}

			PropertyChanges {
				target: applyButton
				visible: true
			}

			PropertyChanges {
				target: lockScreenConnection
				enabled: false
			}

			PropertyChanges {
				target: nextButton
				visible: false
			}
		},
		State {
			name: "Success"
			extend: "RetypePassword"

			PropertyChanges {
				target: successDialog
				visible: true
			}
		}
	]

	ColumnLayout {
		id: columnLayout

		anchors.margins: 20
		anchors.fill: parent
		spacing: 10

		RowLayout {
			id: rowLayout
            Layout.fillWidth: true
			Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

			Button {
				id: cancelButton
				text: qsTr("Anuluj")
				Layout.alignment: Qt.AlignLeft

				Connections {
					onClicked: finished()
				}
			}

			Frame {
				Layout.alignment: Qt.AlignHCenter
				Layout.fillWidth: true

				Label {
					id: label
					anchors.centerIn: parent
					text: qsTr("Proszę wprowadzić stare hasło")
					font.pixelSize: 14
				}
			}

			Button {
				id: nextButton
				Layout.alignment: Qt.AlignRight
				enabled: false
				text: qsTr("Dalej")

				Connections {
					onClicked: {
						newPassword = lockScreen.passwordInput
						lockScreen.passwordInput = ""
						root.state = "RetypePassword"
					}
				}
			}

			Button {
				id: applyButton
				Layout.alignment: Qt.AlignRight
				visible: false
				text: qsTr("Zatwierdź")

				Connections {
					onClicked: {
						retypedNewPassword = lockScreen.passwordInput
						lockScreen.passwordInput = ""
						if (newPassword == retypedNewPassword) {
							Auth.changePassword(retypedNewPassword)
							root.state = "Success"
						} else
							root.state = "MismatchPassword"
					}
				}
			}
		}

		Loader {
			id: lockScreenLoader
			sourceComponent: lockScreenComponent
			Layout.fillHeight: true
			Layout.fillWidth: true
			Layout.alignment: Qt.AlignHCenter
            onLoaded: item.fillMode = Image.PreserveAspectFit

			Connections {
				id: lockScreenConnection
				target: lockScreenLoader.item
				onPasswordInputChanged: {
					// Clearing out passwordInput results in stopping timer
					if (target.passwordInput.length === 0)
						passwordTimer.stop()
					else
						passwordTimer.restart()
				}
				onUnlocked: {
					return root.state == "" ? root.state = "NewPassword" : true
				}
			}
		}
	}

	Timer {
		id: passwordTimer
		interval: 1000
		onTriggered: lockScreen.tryUnlock()
	}

	Dialog {
		id: successDialog

		x: (parent.width - width) / 2
		y: (parent.height - height) / 2
		modal: true
		closePolicy: Popup.NoAutoClose
		title: qsTr("Zmiana hasła")
		standardButtons: Dialog.Ok

		contentItem: Label {
			text: qsTr("Hasło zmieniono pomyślnie!")
			anchors.centerIn: parent
			padding: 30
			font.pixelSize: 14
		}

		onAccepted: finished()
	}

	Dialog {
		id: mismatchPasswordDialog

		x: (parent.width - width) / 2
		y: (parent.height - height) / 2
		modal: true
		closePolicy: Popup.NoAutoClose
		title: qsTr("Zmiana hasła")
		standardButtons: Dialog.Ok

		contentItem: Label {
			text: qsTr('Hasła się nie zgadzają. Proszę ponownie wprowadzić nowe hasło, a następnie nacisnąć przycisk "Dalej".')
			anchors.centerIn: parent
			padding: 30
			font.pixelSize: 14
		}
	}

	Connections {
		onFinished: root.state = ""
	}
}

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
