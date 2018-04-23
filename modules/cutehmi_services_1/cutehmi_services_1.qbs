import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_services_1"

	version: "0.0"

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

//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_1"; cutehmi.metadata.add: true } cutehmi_1.version: "0.0"
//</workaround>

	Export {
		Depends { name: "cutehmi_1" }
	}
}
