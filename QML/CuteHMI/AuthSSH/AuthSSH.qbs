import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_authssh_1_qml"

	files: [
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIAuthSSHQMLPlugin.cpp",
        "src/CuteHMIAuthSSHQMLPlugin.hpp",
    ]

	//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_authssh_1" } cutehmi_authssh_1.version: "0.0"
	//</workaround>
}

