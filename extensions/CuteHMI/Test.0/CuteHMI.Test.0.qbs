import qbs

import cutehmi

Project {
	name: "CuteHMI.Test.0"

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		friendlyName: "Test"

		vendor: "CuteHMI"

		description: "Testing helpers."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "Mozilla Public License, v. 2.0"

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

	SubProject {
		filePath: "tests/tests.qbs"

		Properties {
			condition: parent.buildTests
		}
	}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
