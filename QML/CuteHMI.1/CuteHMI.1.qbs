import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_qml_1"

	version: "0.0"

	vendor: "CuteHMI"

	friendlyName: "Base QML"

	description: "Base CuteHMI extension for all QML applications."

	author: "Wojciech Zygmuntowicz, Michal Policht"

	copyright: "Wojciech Zygmuntowicz, Michal Policht"

	license: "Mozilla Public License, v. 2.0"

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
