import qbs

import cutehmi

cutehmi.QMLPlugin {
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

	//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_1" } cutehmi_1.version: "0.0"
	//</workaround>
}
