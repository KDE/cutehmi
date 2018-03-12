import qbs

QMLPlugin {
	name: "cutehmi_1_qml"

    files: [
        "ColorSet.qml",
        "Element.qml",
        "NumberDisplay.qml",
        "Palette.qml",
        "PropItem.qml",
        "designer/CuteHMI.metainfo",
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMIQMLPlugin.cpp",
        "src/CuteHMIQMLPlugin.hpp",
    ]

	Depends { name: "cutehmi_1" }
}
