import qbs

QMLPlugin {
	name: "cutehmi_app_1_qml"

	files: [
        "designer/App.metainfo",
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIAppQMLPlugin.cpp",
        "src/CuteHMIAppQMLPlugin.hpp",
    ]

	Depends { name: "cutehmi_app_1" }
}

