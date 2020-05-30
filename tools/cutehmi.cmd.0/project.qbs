import qbs 1.0

import cutehmi

Project {
	name: "cutehmi.cmd.0"

	condition: !qbs.targetOS.contains("android")

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Tool {
		name: parent.name

		consoleApplication: true

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Command"

		description: "Console program, which allows one to run QML script."

		files: [
         "README.md",
         "i18n/cutehmi-cmd-0_en.ts",
		 "src/cutehmi/cmd/Exception.cpp",
         "src/cutehmi/cmd/Exception.hpp",
         "src/cutehmi/cmd/logging.cpp",
         "src/cutehmi/cmd/logging.hpp",
         "src/main.cpp",
     ]

		cutehmi.dirs.artifacts: true

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.exclude: ['dev', 'tests']

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.i18n" }
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
