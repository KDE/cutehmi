import QtQuick 2.0
import QtQuick.Dialogs 1.2

import CuteHMI 2.0 as CuteHMI

MessageDialog
{
	property CuteHMI.Dialog dialog

	onDialogChanged: {
		if (dialog) {
			text = dialog.text
			informativeText = dialog.informativeText
			detailedText = dialog.detailedText
			standardButtons = dialog.buttons
			icon = dialog.type
		}
	}

	onClickedButtonChanged: if (dialog) { dialog.acceptResponse(clickedButton); dialog = null }

	onRejected: if (dialog) { dialog.acceptResponse(clickedButton); dialog = null }

	Component.onDestruction: if (dialog) dialog.deleteLater()
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
