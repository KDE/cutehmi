import qbs 1.0

import cutehmi

Project {
	name: "cutehmi_view"

	references: [
		"tests/tests.qbs",
		"examples/examples.qbs"
	]

	cutehmi.Tool {
		name: parent.name

		major: 2

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		friendlyName: "View"

		description: "GUI application, which allows one to run QML project in a window."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
			"README.md",
			"resources.qrc",
			"resources.rc",
			"src/cutehmi/view/logging.cpp",
			"src/cutehmi/view/logging.hpp",
			"src/main.cpp",
		]

		cutehmi.dirs.generateHeaderFile: true

		Depends { name: "CuteHMI.App.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.exclude: ['tests']
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
