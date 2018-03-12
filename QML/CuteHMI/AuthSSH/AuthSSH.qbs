import qbs

QMLPlugin {
	name: "cutehmi_authssh_1_qml"

	files: [
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIAuthSSHQMLPlugin.cpp",
        "src/CuteHMIAuthSSHQMLPlugin.hpp",
    ]

	Depends { name: "cutehmi_authssh_1" }
}

