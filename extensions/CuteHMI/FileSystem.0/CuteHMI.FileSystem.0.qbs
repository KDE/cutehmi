import qbs

import cutehmi

Project {
	name: "CuteHMI.FileSystem.0"

//	references: [
//		"tests/tests.qbs"
//	]

	cutehmi.CppExtension {
		name: parent.name

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "File System"

		description: "Wraps QT file system manipulation classes into QML API."

		author: "Wojciech Zygmuntowicz"

		copyright: "Wojciech Zygmuntowicz"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
			"README.md",
			"include/cutehmi/filesystem/internal/platform.hpp",
			"include/cutehmi/filesystem/internal/common.hpp",
			"include/cutehmi/filesystem/logging.hpp",
			"include/cutehmi/filesystem/metadata.hpp",
			"src/cutehmi/filesystem/internal/QMLPlugin.cpp",
			"src/cutehmi/filesystem/internal/QMLPlugin.hpp",
			"src/cutehmi/filesystem/logging.cpp",
		]

		Depends { name: "CuteHMI.2" }

//		Depends { name: "cutehmi.doxygen" }
//		cutehmi.doxygen.warnIfUndocumented: false
//		cutehmi.doxygen.useDoxyqml: true
//		cutehmi.doxygen.exclude: ['tests']

		Export {
			Depends { name: "CuteHMI.2" }
		}
	}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
