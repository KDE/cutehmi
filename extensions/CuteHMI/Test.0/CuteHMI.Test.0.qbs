import qbs

import cutehmi

Project {
	name: "CuteHMI.Test.0"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		friendlyName: "Test"

		vendor: "CuteHMI"

		description: "Testing helpers."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
			"include/cutehmi/test/IsAnyOfTypes.hpp",
			"include/cutehmi/test/IsIntType.hpp",
			"include/cutehmi/test/internal/common.hpp",
			"include/cutehmi/test/internal/platform.hpp",
			"include/cutehmi/test/logging.hpp",
			"include/cutehmi/test/metadata.hpp",
			"include/cutehmi/test/random.hpp",
			"include/cutehmi/test/tests.hpp",
			"src/cutehmi/test/logging.cpp",
		]

		Depends { name: "Qt.testlib" }

		Depends { name: "CuteHMI.2" }
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
