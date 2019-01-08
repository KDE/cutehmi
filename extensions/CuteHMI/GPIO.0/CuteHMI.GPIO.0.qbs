import qbs

import cutehmi

Project {
	name: "CuteHMI.GPIO.0"

	cutehmi.Extension {
		name: parent.name

		condition: cutehmi.libgpiod.available

		minor: 0

		micro: 0

		friendlyName: "General-purpose Input/Output"

		vendor: "CuteHMI"

		description: "An extension built on top of 'libgpiod' library to deal with GPIO chips."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "Mozilla Public License, v. 2.0"

		files: [
		 "include/cutehmi/gpio/Chip.hpp",
		 "include/cutehmi/gpio/ChipEnumerator.hpp",
		 "include/cutehmi/gpio/Line.hpp",
		 "include/cutehmi/gpio/LineConfig.hpp",
		 "include/cutehmi/gpio/internal/LineEventMonitorThread.hpp",
		 "include/cutehmi/gpio/internal/common.hpp",
		 "include/cutehmi/gpio/internal/platform.hpp",
		 "include/cutehmi/gpio/logging.hpp",
		 "include/cutehmi/gpio/metadata.hpp",
		 "qmldir",
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

		Depends { name: "cutehmi.libgpiod" }

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
