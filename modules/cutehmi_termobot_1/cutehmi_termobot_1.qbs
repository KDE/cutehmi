import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_termobot_1"

	condition: cutehmi.libpq.available

	minor: 0

	micro: 0

	vendor: "CuteHMI"

	friendlyName: "TermoBOT"

	description: "Settings for TermoBOT interface module."

	author: "Wojciech Zygmuntowicz"

	copyright: "Wojciech Zygmuntowicz"

    license: "Mozilla Public License, v. 2.0"

    files: [
        "include/cutehmi/termobot/ContactsModel.hpp",
        "include/cutehmi/termobot/DS18B20SettingsModel.hpp",
        "include/cutehmi/termobot/Exception.hpp",
        "include/cutehmi/termobot/internal/WorkingCounter.hpp",
        "include/cutehmi/termobot/internal/common.hpp",
        "include/cutehmi/termobot/logging.hpp",
        "include/cutehmi/termobot/metadata.hpp",
        "src/cutehmi/termobot/ContactsModel.cpp",
        "src/cutehmi/termobot/DS18B20SettingsModel.cpp",
        "src/cutehmi/termobot/Exception.cpp",
        "src/cutehmi/termobot/DatabaseConnectionData.hpp",
        "src/cutehmi/termobot/DatabaseThread.cpp",
        "src/cutehmi/termobot/DatabaseThread.hpp",
        "src/cutehmi/termobot/Service.cpp",
        "src/cutehmi/termobot/Service.hpp",
        "src/cutehmi/termobot/internal/WorkingCounter.cpp",
        "src/cutehmi/termobot/logging.cpp",
        "src/cutehmi/termobot/plugin/PluginNodeData.cpp",
        "src/cutehmi/termobot/plugin/PluginNodeData.hpp",
        "src/cutehmi/termobot/plugin/ProjectPlugin.cpp",
        "src/cutehmi/termobot/plugin/ProjectPlugin.hpp",
        "src/cutehmi/termobot/plugin/TermobotNodeData.cpp",
        "src/cutehmi/termobot/plugin/TermobotNodeData.hpp",
    ]

    Depends { name: "Qt.concurrent" }
    Depends { name: "Qt.sql" }

    Depends { name: "cutehmi.libpq" }

	Depends { name: "cutehmi_1" }
	cutehmi_1.reqMinor: 0

    Depends { name: "cutehmi_xml_1" }
    cutehmi_xml_1.reqMinor: 0

    Depends { name: "cutehmi_services_1" }
    cutehmi_services_1.reqMinor: 0
}

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
