import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_authssh_qml_1"

	version: "0.0"

	vendor: "CuteHMI"

	friendlyName: "SSH Authentication QML"

	description: "QML components for authentication and tunneling with SSH protocol."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

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

