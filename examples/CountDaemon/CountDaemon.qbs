import qbs

import cutehmi

cutehmi.Example {
	name: "CountDaemon"

	vendor: "CuteHMI"

	friendlyName: "Counting Daemon"

	description: "Daemon demonstration with counter."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "WTFNWPL"

	files: [
        "Main.qml",
    ]

	Depends { name: "cutehmi_daemon" }
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
