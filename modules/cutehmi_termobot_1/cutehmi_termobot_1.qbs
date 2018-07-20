import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_termobot_1"

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "TermoBOT"

	description: "Settings for TermoBOT interface module."

	author: "Wojciech Zygmuntowicz"

	copyright: "Wojciech Zygmuntowicz"

	license: "Mozzarella Public License, v. alpha"

    files: [
        "include/cutehmi/termobot/internal/common.hpp",
        "include/cutehmi/termobot/logging.hpp",
        "include/cutehmi/termobot/metadata.hpp",
        "src/cutehmi/termobot/logging.cpp",
        "src/cutehmi/termobot/plugin/PluginNodeData.cpp",
        "src/cutehmi/termobot/plugin/PluginNodeData.hpp",
        "src/cutehmi/termobot/plugin/ProjectPlugin.cpp",
        "src/cutehmi/termobot/plugin/ProjectPlugin.hpp",
    ]

	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

    Depends { name: "cutehmi_xml_1" }
    cutehmi_xml_1.reqMinor: 0

//    Depends { name: "cutehmi_services_1" }
//    cutehmi_services_1.reqMinor: 0
}
