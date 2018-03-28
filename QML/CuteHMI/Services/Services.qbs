import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_services_1_qml"

	files: [
        "designer/Services.metainfo",
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIServicesQMLPlugin.cpp",
        "src/CuteHMIServicesQMLPlugin.hpp",
    ]

	Depends { name: "cutehmi_services_1" }
}

