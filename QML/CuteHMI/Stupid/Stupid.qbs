import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_stupid_1_qml"

	files: [
        "DS18B20Controller.js",
        "DS18B20Controller.qml",
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIStupidQMLPlugin.cpp",
        "src/CuteHMIStupidQMLPlugin.hpp",
    ]

	//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_stupid_1" } cutehmi_stupid_1.version: "0.0"
	//</workaround>
}

