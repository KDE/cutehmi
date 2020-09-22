import qbs

import cutehmi

Project {
	name: "CuteHMI.SharedDatabase.0"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.CppExtension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Shared Database"

		description: "Shared database connection provider."

		files: [
			"Console.qml",
			"LICENSE.MIT",
			"LICENSE.LGPL3",
			"README.md",
			"include/cutehmi/shareddatabase/DataObject.hpp",
			"include/cutehmi/shareddatabase/Database.hpp",
			"include/cutehmi/shareddatabase/DatabaseWorker.hpp",
			"include/cutehmi/shareddatabase/PostgresMaintenance.hpp",
			"include/cutehmi/shareddatabase/internal/DatabaseConfig.hpp",
			"include/cutehmi/shareddatabase/internal/DatabaseConnectionHandler.hpp",
			"include/cutehmi/shareddatabase/internal/DatabaseThread.hpp",
			"include/cutehmi/shareddatabase/internal/common.hpp",
			"include/cutehmi/shareddatabase/internal/platform.hpp",
			"include/cutehmi/shareddatabase/logging.hpp",
			"include/cutehmi/shareddatabase/metadata.hpp",
			"src/cutehmi/shareddatabase/DataObject.cpp",
			"src/cutehmi/shareddatabase/Database.cpp",
			"src/cutehmi/shareddatabase/DatabaseWorker.cpp",
			"src/cutehmi/shareddatabase/PostgresMaintenance.cpp",
			"src/cutehmi/shareddatabase/internal/DatabaseConfig.cpp",
			"src/cutehmi/shareddatabase/internal/DatabaseConnectionHandler.cpp",
			"src/cutehmi/shareddatabase/internal/DatabaseDictionary.cpp",
			"src/cutehmi/shareddatabase/internal/DatabaseDictionary.hpp",
			"src/cutehmi/shareddatabase/internal/DatabaseThread.cpp",
			"src/cutehmi/shareddatabase/internal/QMLPlugin.cpp",
			"src/cutehmi/shareddatabase/internal/QMLPlugin.hpp",
			"src/cutehmi/shareddatabase/logging.cpp",
		]

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['dev', 'puppet', 'tests']

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.qmldir" }
		cutehmi.qmldir.exclude: ["^designer/.*", "\.js$"]

		Depends { name: "cutehmi.qmltypes" }

		Depends { name: "cutehmi.skeleton.cpp" }
		cutehmi.skeleton.cpp.generateQMLPlugin: true

		Depends { name: "cutehmi.probes.libpq" }	// Using probe just to print some debug output. It is not required to link against client library.

		Depends { name: "Qt.sql" }

		Depends { name: "CuteHMI.Services.2" }

		Export {
			Depends { name: "Qt.sql" }

			Depends { name: "CuteHMI.Services.2" }
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
