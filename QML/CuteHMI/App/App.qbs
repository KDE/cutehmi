import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_app_1_qml"

	files: [
        "designer/App.metainfo",
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIAppQMLPlugin.cpp",
        "src/CuteHMIAppQMLPlugin.hpp",
    ]

	//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_app_1" } cutehmi_app_1.version: "0.0"
	//</workaround>
}

