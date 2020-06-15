import qbs

import cutehmi

Project {
	name: "CuteHMI.Test.0"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		friendlyName: "Test"

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		description: "Testing helpers."

		files: [
			"include/cutehmi/test/IsAnyOfTypes.hpp",
			"include/cutehmi/test/IsIntType.hpp",
			"include/cutehmi/test/internal/common.hpp",
			"include/cutehmi/test/internal/platform.hpp",
			"include/cutehmi/test/logging.hpp",
			"include/cutehmi/test/metadata.hpp",
			"include/cutehmi/test/qml.hpp",
			"include/cutehmi/test/random.hpp",
			"include/cutehmi/test/tests.hpp",
			"src/cutehmi/test/logging.cpp",
			"src/cutehmi/test/qml.cpp",
		]

		cutehmi.dirs.artifacts: true

		Depends { name: "Qt.testlib" }

		Depends { name: "cutehmi.metadata" }

		Depends { name: "CuteHMI.2" }

		Export {
			Depends { name: "CuteHMI.2" }
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
