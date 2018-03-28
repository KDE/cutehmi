import qbs 1.0

import cutehmi

cutehmi.Tool {
	name: "cutehmi_view"

	files: [
        "cutehmi_view.qrc",
        "cutehmi_view.rc",
        "src/main.cpp",
        "src/version.hpp",
    ]

	Depends { name: "cutehmi_1" }
	Depends { name: "cutehmi_xml_1" }
	Depends { name: "cutehmi_app_1" }
}
