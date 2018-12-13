import qbs 1.0

import cutehmi

cutehmi.Tool {
	name: "cutehmi_daemon"

	major: 1

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "Daemon"

	description: "Daemon, which allows one to run CuteHMI project in a background."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "README.md",
        "src/cutehmi/daemon/Daemon.cpp",
        "src/cutehmi/daemon/Daemon.hpp",
        "src/cutehmi/daemon/logging.cpp",
        "src/cutehmi/daemon/logging.hpp",
        "src/main.cpp",
    ]

	Group {
		name: "Windows"
		condition: qbs.targetOS.contains("windows")
		files: [
			"src/cutehmi/daemon/Daemon_win.cpp",
		]
	}
	Group {
		name: "Linux"
		condition: qbs.targetOS.contains("linux")
		files: [
			"src/cutehmi/daemon/Daemon_unix.cpp",
		]
	}

	cutehmi.dirs.generateHeaderFile: true

	Depends { name: "CuteHMI.2" }

//	Depends { name: "cutehmi_xml_1" }
//	cutehmi_xml_1.reqMinor: 0

//	Depends { name: "cutehmi_app_1" }
//	cutehmi_app_1.reqMinor: 0

	Depends { name: "cutehmi.doxygen" }
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
