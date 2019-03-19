import qbs

import cutehmi

Project {
	name: "CuteHMI.BitcoinCash.0"

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		friendlyName: "Bitcoin Cash"

		vendor: "CuteHMI"

		description: "Wraps Bitcoin.com REST API to provide Bitcoin Cash operations."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
			"README.md",
			"include/cutehmi/bitcoincash/Address.hpp",
			"include/cutehmi/bitcoincash/internal/common.hpp",
			"include/cutehmi/bitcoincash/internal/platform.hpp",
			"include/cutehmi/bitcoincash/logging.hpp",
			"include/cutehmi/bitcoincash/metadata.hpp",
			"qmldir",
			"src/cutehmi/bitcoincash/Address.cpp",
			"src/cutehmi/bitcoincash/internal/QMLPlugin.cpp",
			"src/cutehmi/bitcoincash/internal/QMLPlugin.hpp",
			"src/cutehmi/bitcoincash/logging.cpp",
		]

		Depends { name: "Qt.network" }

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['tests']

		Export {
			Depends { name: "CuteHMI.2" }
		}
	}

	SubProject {
		filePath: "tests/tests.qbs"

		Properties {
			condition: parent.buildTests
		}
	}
}

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
