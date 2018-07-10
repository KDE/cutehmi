import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_services_1"

	minor: 0

	micro: 0

	friendlyName: "Services"

	vendor: "CuteHMI"

	description: "Basic facility for dealing with services."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "include/cutehmi/services/Service.hpp",
        "include/cutehmi/services/ServiceRegistry.hpp",
        "include/cutehmi/services/internal/common.hpp",
        "include/cutehmi/services/internal/platform.hpp",
        "include/cutehmi/services/logging.hpp",
        "include/cutehmi/services/metadata.hpp",
        "src/cutehmi/services/Service.cpp",
        "src/cutehmi/services/ServiceRegistry.cpp",
        "src/cutehmi/services/logging.cpp",
        "src/cutehmi/services/plugin/PluginNodeData.cpp",
        "src/cutehmi/services/plugin/PluginNodeData.hpp",
        "src/cutehmi/services/plugin/ProjectPlugin.cpp",
        "src/cutehmi/services/plugin/ProjectPlugin.hpp",
    ]

//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">

	Depends { name: "cutehmi_1"; cutehmi.metadata.add: true } cutehmi_1.reqMinor: 0

	Export {
		Depends { name: "cutehmi_1" } cutehmi_1.reqMinor: 0
	}

//</workaround>
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
