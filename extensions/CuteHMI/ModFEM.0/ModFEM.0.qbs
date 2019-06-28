import qbs

import cutehmi

Project {
	name: "CuteHMI.ModFEM.0"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Extension {
		name: parent.name

		condition: cutehmi.modfem.available

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		friendlyName: "ModFEM"

		description: "Finite elements method provided by ModFEM."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
         "README.md",
         "LICENSE",
         "include/cutehmi/modfem/NavierStokesSUPGHeat.hpp",
         "include/cutehmi/modfem/internal/platform.hpp",
         "include/cutehmi/modfem/internal/common.hpp",
         "include/cutehmi/modfem/logging.hpp",
         "include/cutehmi/modfem/metadata.hpp",
         "qmldir",
         "src/cutehmi/modfem/NavierStokesSUPGHeat.cpp",
         "src/cutehmi/modfem/internal/QMLPlugin.cpp",
         "src/cutehmi/modfem/internal/QMLPlugin.hpp",
         "src/cutehmi/modfem/logging.cpp",
     ]

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.modfem" }

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
