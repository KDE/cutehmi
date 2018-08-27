import qbs

import cutehmi

cutehmi.QMLExtension {
	name: "CuteHMI.Services"

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "Services QML"

	description: "QML components for services."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "designer/Services.metainfo",
        "qmldir",
        "src/CuteHMIServicesQMLPlugin.cpp",
        "src/CuteHMIServicesQMLPlugin.hpp",
    ]

	//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_services_1" }
	cutehmi_services_1.reqMinor: 0
	//</workaround>
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
