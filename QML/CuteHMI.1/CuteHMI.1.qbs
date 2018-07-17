import qbs

import cutehmi

cutehmi.QMLExtension {
	name: "CuteHMI"

	major: 1

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "[Core] QML"

	description: "Base CuteHMI extension for all QML applications."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

    files: [
        "ColorSet.qml",
        "Element.qml",
        "NumberDisplay.qml",
        "Palette.qml",
        "PropItem.qml",
        "README.md",
        "designer/CuteHMI.metainfo",
        "qmldir",
        "src/CuteHMIQMLPlugin.cpp",
        "src/CuteHMIQMLPlugin.hpp",
    ]

	//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0
	//</workaround>

	Depends { name: "cutehmi.doxygen" }
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
