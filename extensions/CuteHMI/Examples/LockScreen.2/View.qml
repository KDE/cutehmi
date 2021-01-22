import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import CuteHMI.Workarounds.Qt.labs.settings 1.0
import CuteHMI.GUI 1.0
import CuteHMI.LockScreen 2.0

ColumnLayout {
	anchors.fill: parent

	GridLayout {
		Layout.alignment: Qt.AlignCenter

		columns: 2

		Button {
			text: qsTr("Lock")

			onClicked: lockPopup.open()
		}

		Switch {
			text: qsTr("Enabled")
			checked: lockPopup.enabled

			onCheckedChanged: lockPopup.enabled = checked
		}

		Label {
			Layout.alignment: Qt.AlignRight

			text: qsTr("Inactivity lock [s]:")
		}

		SpinBox {
			id: timeoutSpinBox

			from: 1
			to: 300
			value: lockPopup.timeout
			editable: true

			onValueChanged: lockPopup.timeout = value
		}

		Button {
			text: qsTr("Delete settings")

			onClicked: deleteSettingsDialog.open()

			Dialog {
				id: deleteSettingsDialog

				anchors.centerIn: parent

				width: 300
				focus: true
				modal: true

				title: qsTr("Delete settings?")
				standardButtons: Dialog.Yes | Dialog.No

				onAccepted: settings.remove("")

				Text {
					width: parent.width
					wrapMode: Text.Wrap

					text: qsTr("Are you sure you want to delete all the stored settings including password? Defaults will be loaded upon restart.")
				}
			}
		}

		Button {
			text: qsTr("Change password")

			onClicked: changePasswordWizzard.open()
		}
	}

	LockPopup {
		id: lockPopup

		z: Number.MAX_VALUE
		width: parent.width
		height: parent.height

		lockItem: CustomLockImage {
			anchors.fill: parent
		}

		property int timeout: 5
	}

	Settings {
		id: settings

		category: "CuteHMI.Examples.LockScreen.2/lockScreen"

		property alias enabled: lockPopup.enabled
		property alias timeout: lockPopup.timeout
		property alias secret: lockPopup.lockItem.secret
	}

	Binding {
		target: CuteApplication
		property: "idleMeasureEnabled"
		value: lockPopup.enabled
	}

	Connections {
		target: CuteApplication

		onIdleChanged: if (lockPopup.enabled && CuteApplication.idle >= lockPopup.timeout) lockPopup.open()
	}

	Popup {
		id: changePasswordWizzard

		width: parent.width
		height: parent.height

		ChangePasswordWizard {
			anchors.fill: parent

			secret: lockPopup.lockItem.secret // If not set, typing old password is not required.

			lockItem: CustomLockImage {
				anchors.fill: parent

				passwordInput.autoAccept: false
				passwordInput.discretion: false
			}

			onAccepted: {
				lockPopup.lockItem.secret = lockItem.secret
				changePasswordWizzard.close()
			}

			onRejected: changePasswordWizzard.close()
		}
	}
}

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
