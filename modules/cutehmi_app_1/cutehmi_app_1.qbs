import qbs

ModuleLib {
    files: [
        "cutehmi_app_1.json",
        "cutehmi_app_1.qrc",
        "include/cutehmi/app/CuteApp.hpp",
        "include/cutehmi/app/MainScreen.hpp",
        "include/cutehmi/app/internal/common.hpp",
        "include/cutehmi/app/internal/platform.hpp",
        "include/cutehmi/app/logging.hpp",
        "src/cutehmi/app/CuteApp.cpp",
        "src/cutehmi/app/MainScreen.cpp",
        "src/cutehmi/app/logging.cpp",
        "src/cutehmi/app/plugin/Plugin.cpp",
        "src/cutehmi/app/plugin/Plugin.hpp",
        "src/cutehmi/app/plugin/PluginNodeData.cpp",
        "src/cutehmi/app/plugin/PluginNodeData.hpp",
        "src/cutehmi/app/plugin/ScreensNodeData.cpp",
        "src/cutehmi/app/plugin/ScreensNodeData.hpp",
    ]
	name: "cutehmi_app_1"

//<workaround ref="cutehmi_app_1-1" target="Qt" cause="bug">
	Depends { name: "Qt.widgets" }
//</workaround>

	Depends { name: "cutehmi_1" }
	Depends { name: "cutehmi_xml_1" }

	Export {
		Depends { name: "Qt.widgets" }

		Depends { name: "cutehmi_1" }
	}
}
