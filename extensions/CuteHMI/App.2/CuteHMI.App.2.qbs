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
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
