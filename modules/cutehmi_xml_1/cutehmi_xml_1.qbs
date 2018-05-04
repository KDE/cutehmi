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

//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_1"; cutehmi.metadata.add: true } cutehmi_1.reqMinor: 0
//</workaround>

	Export {
		Depends { name: "Qt.core" }
		Depends { name: "Qt.qml" }
	}
}
