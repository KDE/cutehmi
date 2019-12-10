import qbs 1.0

import cutehmi

Project {
	name: "cutehmi_view"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Tool {
		name: parent.name

		major: 2

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "View"

		description: "GUI application, which allows one to run QML project in a window."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		// Add also QML files from qrc, because for eg. androiddeployqt needs them installed to scan them.
		files: [
			"README.md",
			"resources.qrc",
			"resources.rc",
			"src/cutehmi/view/logging.cpp",
			"src/cutehmi/view/logging.hpp",
			"src/main.cpp",
			"qml/DefaultScreen.qml",
			"qml/ExtensionLoader.qml",
			"qml/MainWindow.qml",
			"qml/MessageDialog.qml",
			"qml/NotificationListView.qml",
		]

		cutehmi.dirs.artifacts: true

		Depends { name: "CuteHMI.App.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.exclude: ['tests']

		Depends { name: "cutehmi.metadata" }
	}
}

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
