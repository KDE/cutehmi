import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_app_1"

	minor: 0

	micro: 0

	friendlyName: "Application"

	vendor: "CuteHMI"

	description: "Provides foundation for client application."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "include/cutehmi/app/CuteApp.hpp",
        "include/cutehmi/app/MainScreen.hpp",
        "include/cutehmi/app/internal/common.hpp",
        "include/cutehmi/app/internal/platform.hpp",
        "include/cutehmi/app/logging.hpp",
        "include/cutehmi/app/metadata.hpp",
        "src/cutehmi/app/CuteApp.cpp",
        "src/cutehmi/app/MainScreen.cpp",
        "src/cutehmi/app/logging.cpp",
        "src/cutehmi/app/plugin/PluginNodeData.cpp",
        "src/cutehmi/app/plugin/PluginNodeData.hpp",
        "src/cutehmi/app/plugin/ProjectPlugin.cpp",
        "src/cutehmi/app/plugin/ProjectPlugin.hpp",
        "src/cutehmi/app/plugin/ScreensNodeData.cpp",
        "src/cutehmi/app/plugin/ScreensNodeData.hpp",
    ]

//<workaround ref="cutehmi_app_1-1" target="Qt" cause="bug">
	Depends { name: "Qt.widgets" }
//</workaround>

//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

	Depends { name: "cutehmi_xml_1"}
	cutehmi_xml_1.reqMinor: 0

	Export {
		Depends { name: "Qt.widgets" }

		Depends { name: "cutehmi_1" }
		cutehmi_1.reqMinor: 0
	}

//</workaround>
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
