import qbs

import cutehmi

Project {
	name: "CuteHMI.GUI.1"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.PuppetExtension {
		files: [
         "puppet/CuteApplication.qml",
         "puppet/designer/GUI.metainfo",
     ]

		cutehmi.qmldir.singletons: ["CuteApplication"]

		originalExtension: parent.name
	}

	cutehmi.CppExtension {
		name: parent.name

		friendlyName: "Graphical User Interface"

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		description: "Provides foundation for GUI applications."

		files: [
			"Element.qml",
			"LICENSE",
			"NumberDisplay.qml",
			"PropItem.qml",
			"README.md",
			"dev/CuteHMI.GUI-1.workaround.Qt.bug.txt",
			"dev/CuteHMI.GUI-2.workaround.Qt.bug.txt",
			"include/cutehmi/gui/ColorSet.hpp",
			"include/cutehmi/gui/CuteApplication.hpp",
			"include/cutehmi/gui/Fonts.hpp",
			"include/cutehmi/gui/Palette.hpp",
			"include/cutehmi/gui/Theme.hpp",
			"include/cutehmi/gui/Units.hpp",
			"include/cutehmi/gui/internal/common.hpp",
			"include/cutehmi/gui/internal/platform.hpp",
			"include/cutehmi/gui/logging.hpp",
			"include/cutehmi/gui/metadata.hpp",
			"src/cutehmi/gui/ColorSet.cpp",
			"src/cutehmi/gui/CuteApplication.cpp",
			"src/cutehmi/gui/Fonts.cpp",
			"src/cutehmi/gui/Palette.cpp",
			"src/cutehmi/gui/Theme.cpp",
			"src/cutehmi/gui/Units.cpp",
			"src/cutehmi/gui/internal/QMLPlugin.cpp",
			"src/cutehmi/gui/internal/QMLPlugin.hpp",
			"src/cutehmi/gui/logging.cpp",
		]

		Depends { name: "Qt.quick" }

		Depends { name: "CuteHMI.2" }

		//<CuteHMI.GUI-1.workaround target="Qt" cause="bug">
		Depends { name: "Qt.widgets" }
		//</CuteHMI.GUI-1.workaround>

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['dev', 'tests']

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltypes" }

		Export {
			Depends { name: "CuteHMI.2" }

			//<CuteHMI.GUI-1.workaround target="Qt" cause="bug">
			Depends { name: "Qt.widgets" }
			//</CuteHMI.GUI-1.workaround>

			Depends { name: "Qt.quick" }
		}
	}

	cutehmi.AndroidQMLPlugin {
		extensionName: parent.name
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
