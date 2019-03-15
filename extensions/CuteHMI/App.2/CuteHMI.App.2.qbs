import qbs

import cutehmi

Project {
	name: "CuteHMI.App.2"

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		friendlyName: "Application"

		vendor: "CuteHMI"

		description: "Provides foundation for GUI application."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "Mozilla Public License, v. 2.0"

		files: [
         "README.md",
         "include/cutehmi/app/CuteApp.hpp",
         "include/cutehmi/app/internal/common.hpp",
         "include/cutehmi/app/internal/platform.hpp",
         "include/cutehmi/app/logging.hpp",
         "include/cutehmi/app/metadata.hpp",
         "qmldir",
         "src/cutehmi/app/CuteApp.cpp",
         "src/cutehmi/app/internal/QMLPlugin.cpp",
         "src/cutehmi/app/internal/QMLPlugin.hpp",
         "src/cutehmi/app/logging.cpp",
     ]

		Depends { name: "CuteHMI.2" }

		//<CuteHMI.App-1.workaround target="Qt" cause="bug">
		Depends { name: "Qt.widgets" }
		//</CuteHMI.App-1.workaround>

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['tests']

		Export {
			Depends { name: "CuteHMI.2" }

			Depends { name: "Qt.widgets" }
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
