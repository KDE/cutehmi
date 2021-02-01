import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import CuteHMI.LockScreen 2.0

Item {
	id: root

	readonly property string initialState: secret.byteLength !== 0 ? "OLD_PASSWORD" : "NEW_PASSWORD"

	property var secret: new ArrayBuffer

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

			PropertyChanges {
				restoreEntryValues: false
				target: lockItem
				secret: new ArrayBuffer
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

	onSecretChanged: lockItem.secret = secret

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
				if (root.lockItem.gatekeeper.authenticate())
					root.state = "NEW_PASSWORD"
			} else if (root.state === "NEW_PASSWORD") {
				newPassword = root.lockItem.passwordInput.text
				if (newPassword !== "")
					root.lockItem.secret = root.lockItem.gatekeeper.makeSecret(newPassword)
				root.lockItem.passwordInput.reset()
				root.state = "RETYPE_PASSWORD"
			} else if (root.state === "RETYPE_PASSWORD") {
				if (newPassword === root.lockItem.passwordInput.text)
					passwordChangedDialog.open()
				else
					passwordMismatchDialog.open()
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

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
