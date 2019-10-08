import QtQuick 2.0
import QtQuick.Controls 2.0

import CuteHMI 2.0 as CuteHMI

Item {
	id: extensionContainer

	CuteHMI.Dialog {
		id: dialog

		type: CuteHMI.Dialog.CRITICAL
		text: "Could not load extension '" + cutehmi_view_extensionBasename + "." + cutehmi_view_extensionMajor + "'."
		buttons: CuteHMI.Dialog.BUTTON_OK
	}

	Component.onCompleted: {
		if (cutehmi_view_extensionBasename && cutehmi_view_extensionMajor) {
			var qmlData = "import " + cutehmi_view_extensionBasename + " " + cutehmi_view_extensionMajor
			qmlData += "\n" + cutehmi_view_extensionComponent + " { anchors.fill: parent }\n"

			try {
				Qt.createQmlObject(qmlData, extensionContainer)
			} catch(error) {
				showDefaultScreen()
				dialog.informativeText = error.qmlErrors.length > 1 ? qsTr("Reasons: ") : qsTr("Reason: ")
				dialog.informativeText += error.qmlErrors.map(function (obj) { return obj.message }).join("; ") + "."
				createDialog(dialog)
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
