import qbs

import cutehmi

Project {
	name: "CuteHMI.GPIO.0"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		cutehmi.product.enabled: cutehmi.libs.libgpiod.available

		minor: 0

		micro: 0

		friendlyName: "General-purpose Input/Output"

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		description: "An extension built on top of 'libgpiod' library to deal with GPIO chips."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
		 "README.md",
		 "include/cutehmi/gpio/Chip.hpp",
		 "include/cutehmi/gpio/ChipEnumerator.hpp",
		 "include/cutehmi/gpio/Line.hpp",
		 "include/cutehmi/gpio/LineConfig.hpp",
		 "include/cutehmi/gpio/internal/LineEventMonitorThread.hpp",
		 "include/cutehmi/gpio/internal/common.hpp",
		 "include/cutehmi/gpio/internal/platform.hpp",
		 "include/cutehmi/gpio/logging.hpp",
		 "include/cutehmi/gpio/metadata.hpp",
		 "src/cutehmi/gpio/Chip.cpp",
		 "src/cutehmi/gpio/ChipEnumerator.cpp",
		 "src/cutehmi/gpio/Line.cpp",
		 "src/cutehmi/gpio/LineConfig.cpp",
		 "src/cutehmi/gpio/internal/LineEventMonitorThread.cpp",
		 "src/cutehmi/gpio/internal/QMLPlugin.cpp",
		 "src/cutehmi/gpio/internal/QMLPlugin.hpp",
		 "src/cutehmi/gpio/logging.cpp",
	 ]

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.libs.libgpiod" }

//		Depends { name: "cutehmi.doxygen" }
//		cutehmi.doxygen.warnIfUndocumented: false
//		cutehmi.doxygen.useDoxyqml: true
//		cutehmi.doxygen.exclude: ['tests']

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltypes" }

		Export {
			Depends { name: "cutehmi.libs.libgpiod" }

			Depends { name: "CuteHMI.2" }
		}
	}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
