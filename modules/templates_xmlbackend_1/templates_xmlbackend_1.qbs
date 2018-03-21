import qbs

import cutehmi

cutehmi.Module {
	name: "templates_xmlbackend_1"						// Edit!

	minor: 0

	micro: 0

	vendor: "The Secret Order of Templates"			// Edit!

	friendlyName: "XML Backend Template"			// Edit!

	description: "Minimal XML plugin, that can be used as a template for writing plugins."	// Edit!

	author: "Jar Jar"   						    // Edit!

	copyright: "KGB"								// Edit!

	license: "Mozzarella Public License, v. alpha"	// Edit!

	files: [
		"README.md",
		"include/templates/xmlbackend/internal/common.hpp",     // Edit! Fix path.
		"include/templates/xmlbackend/logging.hpp",             // Edit! Fix path.
		"include/templates/xmlbackend/metadata.hpp",            // Edit! Fix path.
		"src/templates/xmlbackend/logging.cpp",                 // Edit! Fix path.
		"src/templates/xmlbackend/plugin/PluginNodeData.cpp",   // Edit! Fix path.
		"src/templates/xmlbackend/plugin/PluginNodeData.hpp",   // Edit! Fix path.
		"src/templates/xmlbackend/plugin/ProjectPlugin.cpp",    // Edit! Fix path.
		"src/templates/xmlbackend/plugin/ProjectPlugin.hpp",    // Edit! Fix path.
	]

	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

	Depends { name: "cutehmi_xml_1" }
	cutehmi_xml_1.reqMinor: 0

	Depends { name: "cutehmi.doxygen" }				// Edit! You may comment out this line to turn off generation of Doxygen artifacts.
}
