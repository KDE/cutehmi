import qbs

import cutehmi

Project {
	name: "CuteHMI.BitcoinCom.0"

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		friendlyName: "Bitcoin.com"

		vendor: "CuteHMI"

		description: "Wraps Bitcoin.com REST API."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "Mozilla Public License, v. 2.0"

		files: [
			"include/cutehmi/bitcoincom/Address.hpp",
			"include/cutehmi/bitcoincom/internal/common.hpp",
			"include/cutehmi/bitcoincom/internal/platform.hpp",
			"include/cutehmi/bitcoincom/logging.hpp",
			"include/cutehmi/bitcoincom/metadata.hpp",
			"src/cutehmi/bitcoincom/Address.cpp",
			"src/cutehmi/bitcoincom/internal/QMLPlugin.cpp",
			"src/cutehmi/bitcoincom/internal/QMLPlugin.hpp",
			"src/cutehmi/bitcoincom/logging.cpp",
		]

		Depends { name: "Qt.network" }

		Depends { name: "CuteHMI.2" }

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
