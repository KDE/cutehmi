import QtQuick 2.0
import QtQuick.Controls 2.0

import CuteHMI 2.0 as CuteHMI

Item {
	id: extensionContainer

	CuteHMI.Message {
		id: message

		type: CuteHMI.Message.CRITICAL
		text: qsTr("Could not load extension '%1'.").arg(cutehmi_view_extensionBasename + (cutehmi_view_extensionMajor ? "." + cutehmi_view_extensionMajor : ""))
		buttons: CuteHMI.Message.BUTTON_OK
	}

	Component.onCompleted: {
		if (cutehmi_view_extensionBasename || cutehmi_view_extensionMajor) {
			var qmlData = "import " + cutehmi_view_extensionBasename + " " + cutehmi_view_extensionMajor
			qmlData += "\n" + cutehmi_view_extensionComponent + " { anchors.fill: parent }\n"

			try {
				Qt.createQmlObject(qmlData, extensionContainer)
			} catch(error) {
				showDefaultScreen()
				message.informativeText = qsTr("Reasons:")
				message.informativeText += "\n" + error.qmlErrors.map(function (obj) { return "- " + obj.message }).join("\n") + "."
				createDialog(message)
			}
		} else {
			showDefaultScreen()
		}
	}

	function showDefaultScreen() {
		var defaultScreenComponent = Qt.createComponent("DefaultScreen.qml")
		var defaultScreen = defaultScreenComponent.createObject(extensionContainer)
		defaultScreen.anchors.centerIn = extensionContainer
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
