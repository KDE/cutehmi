import qbs

import cutehmi

Project {
	condition: false	// This extension no longer works, because Bitcoin.com REST API v1 became unavailable.

	name: "CuteHMI.BitcoinCash.0"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		minor: 0

		micro: 0

		friendlyName: "Bitcoin Cash"

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

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
			"src/cutehmi/bitcoincash/Address.cpp",
			"src/cutehmi/bitcoincash/internal/QMLPlugin.cpp",
			"src/cutehmi/bitcoincash/internal/QMLPlugin.hpp",
			"src/cutehmi/bitcoincash/logging.cpp",
		]

		Depends { name: "Qt.network" }

		Depends { name: "CuteHMI.2" }

//		Depends { name: "cutehmi.doxygen" }
//		cutehmi.doxygen.warnIfUndocumented: false
//		cutehmi.doxygen.useDoxyqml: true
//		cutehmi.doxygen.exclude: ['tests']

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltypes" }

		Export {
			Depends { name: "CuteHMI.2" }
		}
	}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
