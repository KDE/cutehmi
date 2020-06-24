import qbs 1.0

import cutehmi

Project {
	name: "cutehmi.console.0"

	condition: !qbs.targetOS.contains("android")

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Tool {
		name: parent.name

		consoleApplication: true

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Console"

		description: "interactive command line interface, which allows one to browse QML object model and evaluate expressions."

		files: [
         "README.md",
         "i18n/cutehmi-console-0_en.ts",
         "src/cutehmi/console/Command.cpp",
         "src/cutehmi/console/Command.hpp",
         "src/cutehmi/console/Exception.cpp",
         "src/cutehmi/console/Exception.hpp",
         "src/cutehmi/console/InputHandler.cpp",
         "src/cutehmi/console/InputHandler.hpp",
         "src/cutehmi/console/Interpreter.cpp",
         "src/cutehmi/console/Interpreter.hpp",
         "src/cutehmi/console/logging.cpp",
         "src/cutehmi/console/logging.hpp",
         "src/main.cpp",
     ]

		cutehmi.dirs.artifacts: true

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.exclude: ['dev', 'tests', 'src']

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.i18n" }
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
