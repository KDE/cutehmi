import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_stupid_qml_1"

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "STUPiD QML"

	description: "QML extension of STUPiD (Store Temperature Using Pi Daemon)."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "DS18B20Controller.js",
        "DS18B20Controller.qml",
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIStupidQMLPlugin.cpp",
        "src/CuteHMIStupidQMLPlugin.hpp",
    ]

	//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_stupid_1" } cutehmi_stupid_1.reqMinor: 0
	//</workaround>
}

