import qbs

import cutehmi

cutehmi.QMLExtension {
	name: "CuteHMI.Services"

	major: 1

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
	Depends { name: "cutehmi_services_1" } cutehmi_services_1.reqMinor: 0
	//</workaround>
}

