import qbs 1.0

import cutehmi

cutehmi.Tool {
	name: "cutehmi_view"

	major: 1

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "View"

	description: "Client, GUI application, which allows one to run CuteHMI project in a window."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "README.md",
        "resources.qrc",
        "resources.rc",
        "src/main.cpp",
    ]

	property string defaultProject

	property bool virtualKeyboard: false

	cutehmi.dirs.generateHeaderFile: true

	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

	Depends { name: "cutehmi_xml_1" }
	cutehmi_xml_1.reqMinor: 0

	Depends { name: "cutehmi_app_1" }
	cutehmi_app_1.reqMinor: 0

	Depends { name: "cutehmi.doxygen" }

	Properties {
		condition: virtualKeyboard
		cpp.defines: outer.concat("CUTEHMI_VIEW_VIRTUAL_KEYBOARD")
	}

	Properties {
		condition: defaultProject
		cpp.defines: outer.concat("CUTEHMI_VIEW_DEFAULT_PROJECT=\"" + defaultProject + "\"")
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
