import qbs 1.0

import cutehmi

Project {
	name: "cutehmi_daemon"

	references: [
		"tests/tests.qbs",
		"examples/examples.qbs"
	]

	cutehmi.Tool {
		name: parent.name

		consoleApplication: true

		major: 1

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		friendlyName: "Daemon"

		description: "Daemon, which allows one to run QML project in a background."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
         "README.md",
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

		cutehmi.dirs.generateHeaderFile: true

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.exclude: ['tests', 'examples']
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
