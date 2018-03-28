import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_charts_1"

	files: [
        "include/cutehmi/charts/PointSeries.hpp",
        "include/cutehmi/charts/internal/common.hpp",
        "include/cutehmi/charts/internal/platform.hpp",
        "include/cutehmi/charts/logging.hpp",
        "src/cutehmi/charts/PointSeries.cpp",
        "src/cutehmi/charts/logging.cpp",
    ]

	Depends { name: "cutehmi_1" }

	Export {
		Depends { name: "cutehmi_1" }
	}
}
