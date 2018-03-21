import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_stupid_1"

	condition: cutehmi.libpq.available

	minor: 0

	micro: 0

	friendlyName: "STUPiD"

	vendor: "CuteHMI"

	description: "Store Temperature Using Pi Daemon."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "include/cutehmi/stupid/Client.hpp",
        "include/cutehmi/stupid/DS18B20.hpp",
        "include/cutehmi/stupid/DS18B20History.hpp",
        "include/cutehmi/stupid/Service.hpp",
        "include/cutehmi/stupid/internal/AsyncConnector.hpp",
        "include/cutehmi/stupid/internal/CommunicationThread.hpp",
        "include/cutehmi/stupid/internal/DS18B20HistoryWorker.hpp",
        "include/cutehmi/stupid/internal/DatabaseConnectionData.hpp",
        "include/cutehmi/stupid/internal/DatabaseThread.hpp",
        "include/cutehmi/stupid/internal/Worker.hpp",
        "include/cutehmi/stupid/internal/common.hpp",
        "include/cutehmi/stupid/internal/functions.hpp",
        "include/cutehmi/stupid/internal/platform.hpp",
        "include/cutehmi/stupid/logging.hpp",
        "include/cutehmi/stupid/metadata.hpp",
        "src/cutehmi/stupid/Client.cpp",
        "src/cutehmi/stupid/DS18B20.cpp",
        "src/cutehmi/stupid/DS18B20History.cpp",
        "src/cutehmi/stupid/Service.cpp",
        "src/cutehmi/stupid/internal/AsyncConnector.cpp",
        "src/cutehmi/stupid/internal/CommunicationThread.cpp",
        "src/cutehmi/stupid/internal/DS18B20HistoryWorker.cpp",
        "src/cutehmi/stupid/internal/DatabaseThread.cpp",
        "src/cutehmi/stupid/internal/Worker.cpp",
        "src/cutehmi/stupid/internal/functions.cpp",
        "src/cutehmi/stupid/logging.cpp",
        "src/cutehmi/stupid/plugin/PluginNodeData.cpp",
        "src/cutehmi/stupid/plugin/PluginNodeData.hpp",
        "src/cutehmi/stupid/plugin/ProjectPlugin.cpp",
        "src/cutehmi/stupid/plugin/ProjectPlugin.hpp",
        "src/cutehmi/stupid/plugin/StupidNodeData.cpp",
        "src/cutehmi/stupid/plugin/StupidNodeData.hpp",
    ]

	Depends { name: "Qt.concurrent" }
	Depends { name: "Qt.sql" }

	Depends { name: "cutehmi.libpq" }

//<workaround id="qbs-cutehmi-depends-1" target="Qbs" cause="design">

	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

	Depends { name: "cutehmi_xml_1" }
	cutehmi_xml_1.reqMinor: 0

	Depends { name: "cutehmi_services_1" }
	cutehmi_services_1.reqMinor: 0

	Depends { name: "cutehmi_charts_1" }
	cutehmi_charts_1.reqMinor: 0

	Export {
		Depends { name: "Qt.concurrent" }
		Depends { name: "Qt.sql" }

		Depends { name: "cutehmi_1" }
		cutehmi_1.reqMinor: 0

		Depends { name: "cutehmi_charts_1" }
		cutehmi_charts_1.reqMinor: 0
	}

//</workaround>
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
