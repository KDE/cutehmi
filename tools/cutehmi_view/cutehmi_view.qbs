import qbs 1.0

import cutehmi

Project {
	name: "cutehmi_view"

	cutehmi.Tool {
		name: parent.name

		major: 2

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		friendlyName: "View"

		description: "GUI application, which allows one to run QML project in a window."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "Mozilla Public License, v. 2.0"

		files: [
			"README.md",
			"resources.qrc",
			"resources.rc",
			"src/cutehmi/view/logging.cpp",
			"src/cutehmi/view/logging.hpp",
			"src/main.cpp",
		]

		cutehmi.dirs.generateHeaderFile: true

		Depends { name: "CuteHMI.App.2" }

		Depends { name: "cutehmi.doxygen" }
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
