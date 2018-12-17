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

		function createPrompt(prompt) {
			if (prompt) {
				switch (prompt.type) {
					case Prompt.NOTE:
						title = "Note"
						break
					case Prompt.WARNING:
						title = "Warning"
						break
					case Prompt.QUESTION:
						title = "Question"
						break
					case Prompt.CRITICAL:
						title = "Critical"
						break
					default:
						title = "Unrecognized prompt type (" + prompt.type + ")."
				}

				text.text = prompt.text
				informativeText.text = prompt.informativeText
				detailedText.text = prompt.detailedText
				standardButtons = prompt.buttons
			}
		}

		Column {
			Text { id: text }

			Text { id: informativeText }

			Text { id: detailedText }
		}
	}

	TestCase {
		name: "tst_PopupBridgeQML"
		when: windowShown

		function initTestCase() {
			popupBridge.resetAdvertiser(dialog)
		}

		function test_advertise() {
			var prompt = Qt.createQmlObject('
				import CuteHMI 2.0

				Prompt {
					type: Prompt.QUESTION
					text: "Text?"
					informativeText: "Informative text."
					detailedText: "Detailed text."
					buttons: { Prompt.BUTTON_YES | Prompt.BUTTON_NO }
				}', root);

			popupBridge.advertise(prompt)
			waitForRendering(root)

			verify(dialog.standardButton(Dialog.Yes))
			verify(dialog.standardButton(Dialog.No))
		}
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
