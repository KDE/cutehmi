import QtQuick 2.12
import QtQuick.Controls 2.5
import QtTest 1.2

import CuteHMI 2.0

Item {
	id: root

	width: 320
	height: 200

	Dialog {
		id: dialog

		width: 320
		height: 200
		visible: true
		title: "Dialog"

		function createDialog(dialog) {
			if (dialog) {
				switch (dialog.type) {
					case Dialog.NOTE:
						title = "Note"
						break
					case Dialog.WARNING:
						title = "Warning"
						break
					case Dialog.QUESTION:
						title = "Question"
						break
					case Dialog.CRITICAL:
						title = "Critical"
						break
					default:
						title = "Unrecognized dialog type (" + dialog.type + ")."
				}

				text.text = dialog.text
				informativeText.text = dialog.informativeText
				detailedText.text = dialog.detailedText
				standardButtons = dialog.buttons
			}
		}

		Column {
			Text { id: text }

			Text { id: informativeText }

			Text { id: detailedText }
		}
	}

	TestCase {
		name: "Dialogist"
		when: windowShown

		function initTestCase() {
			dialogist.resetAdvertiser(dialog)
		}

		function test_advertise() {
			var dialog = Qt.createQmlObject('
				import CuteHMI 2.0

				Dialog {
					type: Dialog.QUESTION
					text: "Text?"
					informativeText: "Informative text."
					detailedText: "Detailed text."
					buttons: { Dialog.BUTTON_YES | Dialog.BUTTON_NO }
				}', root);

			dialogist.advertise(dialog)
			waitForRendering(root)

			verify(dialog.standardButton(Dialog.Yes))
			verify(dialog.standardButton(Dialog.No))
		}
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
