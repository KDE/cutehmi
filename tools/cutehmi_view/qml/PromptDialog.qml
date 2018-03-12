import QtQuick 2.0
import QtQuick.Dialogs 1.2

import CuteHMI 1.0

MessageDialog
{
	property Prompt prompt

	onPromptChanged: {
		if (prompt) {
			text = prompt.text
			informativeText = prompt.informativeText
			detailedText = prompt.detailedText
			standardButtons = prompt.buttons
			icon = prompt.type
		}
	}

	onClickedButtonChanged: if (prompt) { prompt.acceptResponse(clickedButton); prompt = null }

	onRejected: if (prompt) { prompt.acceptResponse(clickedButton); prompt = null }

	Component.onDestruction: if (prompt) prompt.deleteLater()
}
