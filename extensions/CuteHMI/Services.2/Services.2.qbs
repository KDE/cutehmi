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

		Depends { name: "cutehmi.init" }
		cutehmi.init.initializerClass: "cutehmi::services::Initializer"

//		Depends { name: "cutehmi.doxygen" }
//		cutehmi.doxygen.warnIfUndocumented: false
//		cutehmi.doxygen.useDoxyqml: true
//		cutehmi.doxygen.exclude: ['tests']

		Export {
			Depends { name: "CuteHMI.2" }
		}
	}
}

//(c)C: Copyright © 2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
