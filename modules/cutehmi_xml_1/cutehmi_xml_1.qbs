import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_xml_1"

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "XML"

	description: "Provides XML facilities for other modules."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "README.md",
        "include/cutehmi/xml/BackendPlugin.hpp",
        "include/cutehmi/xml/IBackendPlugin.hpp",
        "include/cutehmi/xml/ParseAttribute.hpp",
        "include/cutehmi/xml/ParseElement.hpp",
        "include/cutehmi/xml/ParseHelper.hpp",
        "include/cutehmi/xml/ProjectBackend.hpp",
        "include/cutehmi/xml/conversions.hpp",
        "include/cutehmi/xml/internal/common.hpp",
        "include/cutehmi/xml/internal/functions.hpp",
        "include/cutehmi/xml/internal/platform.hpp",
        "include/cutehmi/xml/logging.hpp",
        "include/cutehmi/xml/metadata.hpp",
        "src/cutehmi/xml/BackendPlugin.cpp",
        "src/cutehmi/xml/ParseAttribute.cpp",
        "src/cutehmi/xml/ParseElement.cpp",
        "src/cutehmi/xml/ParseHelper.cpp",
        "src/cutehmi/xml/ProjectBackend.cpp",
        "src/cutehmi/xml/conversions.cpp",
        "src/cutehmi/xml/internal/functions.cpp",
        "src/cutehmi/xml/logging.cpp",
        "src/cutehmi/xml/plugin/MetadataPlugin.hpp",
    ]

	Depends { name: "Qt.core" }
	Depends { name: "Qt.qml" }

//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0
//</workaround>

	Depends { name: "cutehmi.doxygen" }
	cutehmi.doxygen.warnIfUndocumented: false

	Export {
		Depends { name: "Qt.core" }
		Depends { name: "Qt.qml" }
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
