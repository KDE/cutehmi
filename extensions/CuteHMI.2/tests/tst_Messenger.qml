import QtQuick 2.12
import QtQuick.Controls 2.5
import QtTest 1.2

import CuteHMI 2.0 as CuteHMI

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

		function createDialog(message) {
			if (message) {
				switch (message.type) {
					case CuteHMI.Message.NOTE:
						title = "Note"
						break
					case CuteHMI.Message.WARNING:
						title = "Warning"
						break
					case CuteHMI.Message.QUESTION:
						title = "Question"
						break
					case CuteHMI.Message.CRITICAL:
						title = "Critical"
						break
					default:
						title = "Unrecognized dialog type (" + message.type + ")."
				}

				text.text = message.text
				informativeText.text = message.informativeText
				detailedText.text = message.detailedText
				standardButtons = message.buttons
			}
		}

		Column {
			Text { id: text }

			Text { id: informativeText }

			Text { id: detailedText }
		}
	}

	TestCase {
		name: "Messenger"
		when: windowShown

		function initTestCase() {
			messenger.resetAdvertiser(dialog)
		}

		function test_advertise() {
			var message = Qt.createQmlObject('
				import CuteHMI 2.0

				Message {
					type: Message.QUESTION
					text: "Text?"
					informativeText: "Informative text."
					detailedText: "Detailed text."
					buttons: { Message.BUTTON_YES | Message.BUTTON_NO }
				}', root);

			messenger.advertise(message)
			waitForRendering(root)

			verify(dialog.standardButton(Dialog.Yes))
			verify(dialog.standardButton(Dialog.No))
		}
	}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
