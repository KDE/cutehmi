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

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
