import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_services_1"

	files: [
        "cutehmi_services_1.json",
        "cutehmi_services_1.qrc",
        "include/cutehmi/services/Service.hpp",
        "include/cutehmi/services/ServiceRegistry.hpp",
        "include/cutehmi/services/internal/common.hpp",
        "include/cutehmi/services/internal/platform.hpp",
        "include/cutehmi/services/logging.hpp",
        "src/cutehmi/services/Service.cpp",
        "src/cutehmi/services/ServiceRegistry.cpp",
        "src/cutehmi/services/logging.cpp",
        "src/cutehmi/services/plugin/Plugin.cpp",
        "src/cutehmi/services/plugin/Plugin.hpp",
        "src/cutehmi/services/plugin/PluginNodeData.cpp",
        "src/cutehmi/services/plugin/PluginNodeData.hpp",
    ]

	Depends { name: "cutehmi_1" }

	Export {
		Depends { name: "cutehmi_1" }
	}
}
