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

	//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_services_1" } cutehmi_services_1.version: "0.0"
	//</workaround>
}

