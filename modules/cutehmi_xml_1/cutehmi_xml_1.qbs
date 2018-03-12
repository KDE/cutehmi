import qbs

ModuleLib {
	name: "cutehmi_xml_1"

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
        "src/cutehmi/xml/BackendPlugin.cpp",
        "src/cutehmi/xml/ParseAttribute.cpp",
        "src/cutehmi/xml/ParseElement.cpp",
        "src/cutehmi/xml/ParseHelper.cpp",
        "src/cutehmi/xml/ProjectBackend.cpp",
        "src/cutehmi/xml/conversions.cpp",
        "src/cutehmi/xml/internal/functions.cpp",
		"src/cutehmi/xml/logging.cpp",
    ]

	Depends { name: "Qt.core" }
	Depends { name: "Qt.qml" }

	Depends { name: "cutehmi_1" }

	Export {
		Depends { name: "Qt.core" }
		Depends { name: "Qt.qml" }
	}
}
