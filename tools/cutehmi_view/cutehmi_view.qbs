import qbs 1.0

import cutehmi

cutehmi.Tool {
	name: "cutehmi_view"

	major: 1

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "View"

	description: "Client application, which allows for opening and viewing CuteHMI projects."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "resources.qrc",
        "resources.rc",
        "src/main.cpp",
    ]

	Depends { name: "cutehmi_1" } cutehmi_1.reqMinor: 0
	Depends { name: "cutehmi_xml_1" } cutehmi_xml_1.reqMinor: 0
	Depends { name: "cutehmi_app_1" } cutehmi_app_1.reqMinor: 0
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
