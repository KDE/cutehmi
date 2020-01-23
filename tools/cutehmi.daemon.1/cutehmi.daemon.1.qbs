import qbs 1.0

import cutehmi

Project {
	name: "cutehmi.daemon.1"

	condition: !qbs.targetOS.contains("android")

	references: [
		"tests/tests.qbs",
		"examples/examples.qbs"
	]

	cutehmi.Tool {
		name: parent.name

		consoleApplication: true

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Daemon"

		description: "Daemon, which allows one to run QML project in a background."

		files: [
         "README.md",
         "dev/cutehmi.daemon.1-1.workaround.Qt.QTBUG-73649.txt",
         "src/cutehmi/daemon/CoreData.hpp",
         "src/cutehmi/daemon/Daemon.cpp",
         "src/cutehmi/daemon/Daemon.hpp",
         "src/cutehmi/daemon/Exception.cpp",
         "src/cutehmi/daemon/Exception.hpp",
         "src/cutehmi/daemon/logging.cpp",
         "src/cutehmi/daemon/logging.hpp",
         "src/main.cpp",
     ]

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
		cutehmi.doxygen.exclude: ['dev', 'examples', 'tests']

		Depends { name: "cutehmi.metadata" }
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
