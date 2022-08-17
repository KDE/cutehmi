import qbs 1.0

import cutehmi

Project {
	name: "cutehmi.view.4"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Tool {
		name: parent.name

		consoleApplication: false

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "View"

		description: "GUI application, which allows one to run QML project in a window."

		i18n: true

		// Add also QML files from qrc, because for eg. androiddeployqt needs them installed to scan them.
		files: [
         "README.md",
         "dev/cutehmi.view.2-1.solved.Qt.design.txt",
         "dev/cutehmi.view.2-2.unsolved.Qt.bug.txt",
         "dev/cutehmi.view.2-3.solved.Qt.bug.txt",
         "dev/cutehmi.view.2-4.workaround.Qt.bug.txt",
         "dev/cutehmi.view.2-5.workaround.Qt.bug.txt",
         "dev/cutehmi.view.2-6.workaround.Qt.bug.txt",
         "i18n/cutehmi-view-4_en_US.ts",
         "i18n/cutehmi-view-4_pl.ts",
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

		Properties {
			condition: project.windeployqt
			cutehmi.windeployqt.qmldir: sourceDirectory + "/qml"
		}

		property string defaultExtension

		property string defaultMinor

		property string defaultInit

		property string defaultComponent

		property string defaultLanguage

		property bool forceDefaultOptions: false

		property bool virtualKeyboard: false

		cpp.defines: {
			var result = []

			if (virtualKeyboard)
				result.push("CUTEHMI_VIEW_VIRTUAL_KEYBOARD")

			if (defaultExtension)
				result.push("CUTEHMI_VIEW_DEFAULT_EXTENSION=\"" + defaultExtension + "\"")

			if (defaultMinor)
				result.push("CUTEHMI_VIEW_DEFAULT_MINOR=\"" + defaultMinor + "\"")

			if (defaultInit)
				result.push("CUTEHMI_VIEW_DEFAULT_INIT=\"" + defaultInit + "\"")

			if (defaultComponent)
				result.push("CUTEHMI_VIEW_DEFAULT_COMPONENT=\"" + defaultComponent + "\"")

			if (forceDefaultOptions)
				result.push("CUTEHMI_VIEW_FORCE_DEFAULT_OPTIONS")

			if (defaultLanguage)
				result.push("CUTEHMI_VIEW_DEFAULT_LANGUAGE=\"" + defaultLanguage + "\"")

			return result
		}

		cutehmi.dirs.artifacts: true

		Depends { name: "CuteHMI.GUI.1" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.exclude: ['dev', 'tests', 'src']

		Depends { name: "cutehmi.i18n" }

		Export {
			Depends { name: "CuteHMI.GUI.1" }
		}
	}
}

//(c)C: Copyright © 2020-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
