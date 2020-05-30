import QtQuick 2.0

import CuteHMI 2.0 as CuteHMI

QtObject {
	id: extensionContainer

	Component.onCompleted: {
		if (cutehmi_daemon_extensionBaseName || cutehmi_daemon_extensionMajor || cutehmi_daemon_extensionMinor) {
			var qmlData = "import " + cutehmi_daemon_extensionBaseName + " " + cutehmi_daemon_extensionMajor + "." + cutehmi_daemon_extensionMinor
			qmlData += "\n" + cutehmi_daemon_extensionComponent + " {}\n"

			try {
				Qt.createQmlObject(qmlData, extensionContainer)
			} catch(error) {
				var informativeText = qsTr("Reasons:")
				informativeText += "\n" + error.qmlErrors.map(function (obj) { return "- " + obj.message }).join("\n") + "."

				var extensionName = cutehmi_daemon_extensionBaseName + " " + cutehmi_daemon_extensionMajor + "." + cutehmi_daemon_extensionMinor
				console.error(qsTr("Could not load extension '%1'.").arg(extensionName))
				console.error(informativeText)
				Qt.exit(1)
			}
		} else {
			console.log("No extension specified.")
			console.log("Use --help to see available options.")
			Qt.quit()
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
