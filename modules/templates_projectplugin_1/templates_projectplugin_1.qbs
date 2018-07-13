import qbs

import cutehmi

cutehmi.Module {
	name: "templates_projectplugin_1"               // Edit!

	minor: 0

	micro: 0

	vendor: "The Secret Order of Templates"         // Edit!

	friendlyName: "Project Plugin Template"         // Edit!

	description: "Minimalistic plugin, that can be used as a template for writing plugins."    // Edit!

	author: "Darth Bane"                            // Edit!

	copyright: "KGB"                                // Edit!

	license: "Mozzarella Public License, v. alpha"  // Edit!

	files: [
        "README.md",
        "include/templates/projectplugin/internal/common.hpp",
        "include/templates/projectplugin/logging.hpp",
        "include/templates/projectplugin/metadata.hpp",
        "src/templates/projectplugin/logging.cpp",
        "src/templates/projectplugin/plugin/PluginNodeData.cpp",
        "src/templates/projectplugin/plugin/PluginNodeData.hpp",
        "src/templates/projectplugin/plugin/ProjectPlugin.cpp",
        "src/templates/projectplugin/plugin/ProjectPlugin.hpp",
    ]

	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

	Depends { name: "cutehmi.doxygen" }             // Edit! You may comment out this line to turn off generation of Doxygen artifacts.
}

