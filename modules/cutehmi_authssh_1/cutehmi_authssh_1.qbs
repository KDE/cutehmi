import qbs

import cutehmi

cutehmi.Module {
	name: "cutehmi_authssh_1"

	version: "0.0"

	friendlyName: "SSH Authentication"

	vendor: "CuteHMI"

	description: "Authentication and tunneling with SSH protocol."

	author: "Michal Policht"

	copyright: "Michal Policht"

	license: "Mozilla Public License, v. 2.0"

	files: [
        "include/cutehmi/authssh/AbstractChannel.hpp",
        "include/cutehmi/authssh/Client.hpp",
        "include/cutehmi/authssh/Exception.hpp",
        "include/cutehmi/authssh/ForwardChannel.hpp",
        "include/cutehmi/authssh/Session.hpp",
        "include/cutehmi/authssh/internal/ChannelsThread.hpp",
        "include/cutehmi/authssh/internal/TunnelEntrance.hpp",
        "include/cutehmi/authssh/internal/common.hpp",
        "include/cutehmi/authssh/internal/platform.hpp",
        "include/cutehmi/authssh/logging.hpp",
        "include/cutehmi/authssh/metadata.hpp",
        "src/cutehmi/authssh/AbstractChannel.cpp",
        "src/cutehmi/authssh/Client.cpp",
        "src/cutehmi/authssh/ForwardChannel.cpp",
        "src/cutehmi/authssh/Session.cpp",
        "src/cutehmi/authssh/internal/ChannelsThread.cpp",
        "src/cutehmi/authssh/internal/TunnelEntrance.cpp",
        "src/cutehmi/authssh/logging.cpp",
        "src/cutehmi/authssh/plugin/AuthSSHNodeData.cpp",
        "src/cutehmi/authssh/plugin/AuthSSHNodeData.hpp",
        "src/cutehmi/authssh/plugin/PluginNodeData.cpp",
        "src/cutehmi/authssh/plugin/PluginNodeData.hpp",
        "src/cutehmi/authssh/plugin/ProjectPlugin.cpp",
        "src/cutehmi/authssh/plugin/ProjectPlugin.hpp",
    ]

	Depends { name: "Qt.network" }

//<workaround id="qbs.cutehmi.depends-1" target="Qbs" cause="design">
	Depends { name: "cutehmi_1"; cutehmi.metadata.add: true } cutehmi_1.version: "0.0"
	Depends { name: "cutehmi_xml_1"; cutehmi.metadata.add: true } cutehmi_xml_1.version: "0.0"

	Depends { name: "cutehmi.libssh" }

	Export {
		Depends { name: "Qt.network" }

		Depends { name: "cutehmi_1" } cutehmi_1.version: "0.0"

		Depends { name: "cutehmi.libssh" }
	}
//</workaround>
}
