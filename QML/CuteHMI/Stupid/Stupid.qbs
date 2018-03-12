import qbs

QMLPlugin {
	name: "cutehmi_stupid_1_qml"

	files: [
        "DS18B20Controller.js",
        "DS18B20Controller.qml",
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIStupidQMLPlugin.cpp",
        "src/CuteHMIStupidQMLPlugin.hpp",
    ]

	Depends { name: "cutehmi_stupid_1" }
}

