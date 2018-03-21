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

//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">

	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

	Export {
		Depends { name: "cutehmi_1" }
		cutehmi_1.reqMinor: 0
	}

//</workaround>
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
