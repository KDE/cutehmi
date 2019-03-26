import qbs

import cutehmi

Project {
	name: "Templates.Skeleton.0"

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		vendor: "The Secret Order of Templates"

		friendlyName: "Skeleton"

		description: "Extension skeleton."

		author: "Michal Policht"

		copyright: "Anyone"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
			"README.md",
			"LICENSE",
//			"include/templates/skeleton/internal/platform.hpp",
//			"include/templates/skeleton/internal/common.hpp",
//			"include/templates/skeleton/logging.hpp",
//			"include/templates/skeleton/metadata.hpp",
//			"src/templates/skeleton/logging.cpp",
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
