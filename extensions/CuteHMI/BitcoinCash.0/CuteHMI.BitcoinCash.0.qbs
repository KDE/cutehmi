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

		license: "Mozilla Public License, v. 2.0"

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

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
