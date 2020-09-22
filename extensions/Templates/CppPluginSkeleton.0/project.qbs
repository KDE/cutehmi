import qbs

import cutehmi

Project {
	name: "Templates.CppPluginSkeleton.0"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		vendor: "The Secret Order of Templates"

		domain: "xn--cuthmi-5of.kde.org"

		friendlyName: "C++ Plugin Skeleton"

		description: "Skeletal C++ extension with QML plugin."

		files: [
			"README.md",
			"LICENSE.MIT",
			"LICENSE.LGPL3",
			"include/templates/cpppluginskeleton/Exception.hpp",
			"include/templates/cpppluginskeleton/Init.hpp",
			"include/templates/cpppluginskeleton/internal/platform.hpp",
			"include/templates/cpppluginskeleton/internal/common.hpp",
			"include/templates/cpppluginskeleton/logging.hpp",
			"include/templates/cpppluginskeleton/metadata.hpp",
			"src/templates/cpppluginskeleton/Init.cpp",
			"src/templates/cpppluginskeleton/internal/QMLPlugin.cpp",
			"src/templates/cpppluginskeleton/internal/QMLPlugin.hpp",
			"src/templates/cpppluginskeleton/logging.cpp",
		]

		Depends { name: "CuteHMI.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.exclude: ['tests']

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltypes" }

		Depends { name: "cutehmi.skeleton.cpp" }
		cutehmi.skeleton.cpp.generateQMLPlugin: true
		cutehmi.skeleton.cpp.generateException: true
		cutehmi.skeleton.cpp.generateInit: true

		Export {
			Depends { name: "CuteHMI.2" }
		}
	}
}

//(c)ANYONE: Copyright © 2020, Anyone. All rights reserved.
//(c)ANYONE: This file is a part of CuteHMI.
//(c)ANYONE: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)ANYONE: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)ANYONE: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
