import qbs

import cutehmi

//<qbs-imports-cutehmi-4.workaround target="QtCreator_Windows" cause="missing">

Project {
	name: "CuteHMI.Workarounds.PuppetBootloader.0"

	cutehmi.CppExtension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Puppet Bootloader"

		description: "Hackish initialization plugin intended to be used by Qt Creator in Design mode."

		files: [
			"src/cutehmi/workarounds/puppetbootloader/internal/Init.cpp",
			"src/cutehmi/workarounds/puppetbootloader/internal/Init.hpp",
			"src/cutehmi/workarounds/puppetbootloader/internal/QMLPlugin.cpp",
			"src/cutehmi/workarounds/puppetbootloader/internal/QMLPlugin.hpp",
		]

		Group {
			name: "Windows"
			condition: qbs.targetOS.contains("windows")
			files: [
				"src/cutehmi/workarounds/puppetbootloader/internal/Init_win.cpp",
			]
		}

		Group {
			name: "Generic"
			condition: !qbs.targetOS.contains("windows")
			files: [
				"src/cutehmi/workarounds/puppetbootloader/internal/Init_generic.cpp",
			]
		}


		Depends { name: "Qt.core" }

		Depends { name: "Qt.qml" }
	}
}

//</qbs-imports-cutehmi-4.workaround>

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
