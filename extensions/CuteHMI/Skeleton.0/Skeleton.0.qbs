import qbs

import cutehmi

Project {
	name: "CuteHMI.Skeleton.0"

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		friendlyName: "Skeleton"

		description: "Extension skeleton."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
			"README.md",
//			"include/cutehmi/skeleton/internal/platform.hpp",
//			"include/cutehmi/skeleton/internal/common.hpp",
//			"include/cutehmi/skeleton/logging.hpp",
//			"include/cutehmi/skeleton/metadata.hpp",
//			"src/cutehmi/skeleton/logging.cpp",
		]

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['tests']

		Export {
			Depends { name: "CuteHMI.2" }
		}
	}

//	SubProject {
//		filePath: "tests/tests.qbs"

//		Properties {
//			condition: parent.buildTests
//		}
//	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
