import qbs

import cutehmi

Project {
	name: "Templates.Skeleton.0"

//	references: [
//		"tests/tests.qbs"
//	]

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		vendor: "The Secret Order of Templates"

		domain: "stemplates.org"

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
}

//(c)ANYONE: Copyright © 2019, Anyone. All rights reserved.
//(c)ANYONE: This file is a part of CuteHMI.
//(c)ANYONE: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)ANYONE: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)ANYONE: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
