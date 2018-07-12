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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
