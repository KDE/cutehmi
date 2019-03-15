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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
