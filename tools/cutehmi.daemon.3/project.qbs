import qbs 1.0

import cutehmi

Project {
	name: "cutehmi.daemon.3"

	condition: !qbs.targetOS.contains("android")

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Tool {
		name: parent.name

		consoleApplication: true

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Daemon"

		description: "Console program, which allows one to run QML project in the background."

		files: [
         "README.md",
         "dev/cutehmi.daemon-1.workaround.Qt.QTBUG-73649.txt",
         "qml/ExtensionLoader.qml",
         "resources.qrc",
         "src/cutehmi/daemon/CoreData.hpp",
         "src/cutehmi/daemon/Daemon.cpp",
         "src/cutehmi/daemon/Daemon.hpp",
         "src/cutehmi/daemon/Exception.cpp",
         "src/cutehmi/daemon/Exception.hpp",
         "src/cutehmi/daemon/logging.cpp",
         "src/cutehmi/daemon/logging.hpp",
         "src/main.cpp",
     ]

		property string defaultExtension

		property string defaultMinor

		property string defaultInit

		property string defaultComponent

//		property string defaultLanguage

		property bool forceDefaultOptions: false

		Properties {
			condition: project.windeployqt
			cutehmi.windeployqt.qmldir: sourceDirectory + "/qml"
		}

		cpp.defines: {
			var result = []

			if (defaultExtension)
				result.push("CUTEHMI_DAEMON_DEFAULT_EXTENSION=\"" + defaultExtension + "\"")

			if (defaultMinor)
				result.push("CUTEHMI_DAEMON_DEFAULT_MINOR=\"" + defaultMinor + "\"")

			if (defaultInit)
				result.push("CUTEHMI_DAEMON_DEFAULT_INIT=\"" + defaultInit + "\"")

			if (defaultComponent)
				result.push("CUTEHMI_DAEMON_DEFAULT_COMPONENT=\"" + defaultComponent + "\"")

			if (forceDefaultOptions)
				result.push("CUTEHMI_DAEMON_FORCE_DEFAULT_OPTIONS")

//			if (defaultLanguage)
//				result.push("CUTEHMI_DAEMON_DEFAULT_LANGUAGE=\"" + defaultLanguage + "\"")

			return result
		}

		Group {
			name: "Windows"
			condition: qbs.targetOS.contains("windows")
			files: [
				"src/cutehmi/daemon/Daemon_win.cpp",
			]
		}
		Group {
			name: "Linux"
			condition: qbs.targetOS.contains("linux")
			files: [
				"src/cutehmi/daemon/Daemon_unix.cpp",
				"src/cutehmi/daemon/Daemon_unix.hpp"
			]
		}

		cutehmi.dirs.artifacts: true

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.exclude: ['dev', 'tests', 'src']
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
