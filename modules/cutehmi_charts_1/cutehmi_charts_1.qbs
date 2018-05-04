import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_charts_1"

	minor: 0

	micro: 0

	friendlyName: "Charts"

	vendor: "CuteHMI"

	description: "Data visualization charts."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "include/cutehmi/charts/PointSeries.hpp",
        "include/cutehmi/charts/internal/common.hpp",
        "include/cutehmi/charts/internal/platform.hpp",
        "include/cutehmi/charts/logging.hpp",
        "include/cutehmi/charts/metadata.hpp",
        "src/cutehmi/charts/PointSeries.cpp",
        "src/cutehmi/charts/logging.cpp",
        "src/cutehmi/charts/plugin/MetadataPlugin.hpp",
    ]

//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">

	Depends { name: "cutehmi_1"; cutehmi.metadata.add: true } cutehmi_1.reqMinor: 0

	Export {
		Depends { name: "cutehmi_1" } cutehmi_1.reqMinor: 0
	}

//</workaround>
}
