import qbs

import cutehmi

Project {
	name: "CuteHMI.Services.2"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Services"

		description: "Extension that helps creating services."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
         "README.md",
         "LICENSE",
         "dev/StandardStates.scxml",
         "include/cutehmi/services/Initializer.hpp",
         "include/cutehmi/services/PollingTimer.hpp",
         "include/cutehmi/services/Service.hpp",
         "include/cutehmi/services/ServiceListModel.hpp",
         "include/cutehmi/services/ServiceManager.hpp",
         "include/cutehmi/services/Serviceable.hpp",
         "include/cutehmi/services/internal/QMLPlugin.cpp",
         "include/cutehmi/services/internal/QMLPlugin.hpp",
         "include/cutehmi/services/internal/StateInterface.hpp",
         "include/cutehmi/services/internal/platform.hpp",
         "include/cutehmi/services/internal/common.hpp",
         "include/cutehmi/services/logging.hpp",
         "include/cutehmi/services/metadata.hpp",
         "qmldir",
         "src/cutehmi/services/Initializer.cpp",
         "src/cutehmi/services/PollingTimer.cpp",
         "src/cutehmi/services/Service.cpp",
         "src/cutehmi/services/ServiceListModel.cpp",
         "src/cutehmi/services/ServiceManager.cpp",
         "src/cutehmi/services/internal/StateInterface.cpp",
         "src/cutehmi/services/logging.cpp",
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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
