import qbs

import cutehmi

cutehmi.Module {
	name: "templates_minimal_1"                     // Edit!

	minor: 0

	micro: 0

	vendor: "The Secret Order of Templates"         // Edit!

	friendlyName: "Minimal Module Template"         // Edit!

	description: "Minimalistic module, that can be used as a template for writing modules."    // Edit!

	author: "Sheev Palpatine"                       // Edit!

	copyright: "KGB"                                // Edit!

	license: "Mozzarella Public License, v. alpha"  // Edit!

	files: [
        "README.md",
        "include/templates/minimal/internal/common.hpp",
        "include/templates/minimal/logging.hpp",
        "include/templates/minimal/metadata.hpp",
        "src/templates/minimal/logging.cpp",
    ]

	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

	Depends { name: "cutehmi.doxygen" }             // Edit! You may comment out this line to turn off generation of Doxygen artifacts.
}
